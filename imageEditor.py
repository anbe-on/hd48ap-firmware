import re
from flask import Flask, render_template_string, jsonify, request

app = Flask(__name__)
WIDTH = 64
HEIGHT = 64
BYTES_EXPECTED = WIDTH * (HEIGHT // 8)  # 512

# Automatically parse keymap.c
def load_frames_from_c(file_path="keymaps/default/keymap.c"):
    with open(file_path, "r") as f:
        content = f.read()

    # Match array of frames
    pattern = re.compile(
        r"static\s+const\s+char\s+PROGMEM\s+image_frames\s*\[\s*\]\s*\[\s*512\s*\]\s*=\s*\{(.*?)\};",
        re.S
    )
    match = pattern.search(content)
    if not match:
        raise ValueError("image_frames not found in keymap.c")

    frames_text = match.group(1)

    # Split into individual frames
    frame_pattern = re.compile(r"\{(.*?)\}", re.S)
    frames = []
    for frame_match in frame_pattern.finditer(frames_text):
        frame_data = frame_match.group(1)
        # Extract all hex numbers
        bytes_list = [int(b, 16) for b in re.findall(r"0x([0-9a-fA-F]{2})", frame_data)]
        if len(bytes_list) != BYTES_EXPECTED:
            raise ValueError(f"A frame has {len(bytes_list)} bytes, expected {BYTES_EXPECTED}")
        frames.append(bytes_list)

    return frames

image_frames = load_frames_from_c()

# Pixel expansion
def expand_pixels(bytes_list):
    pixels = [0] * (WIDTH * HEIGHT)
    for x in range(WIDTH):
        for byte_row in range(HEIGHT // 8):
            b = bytes_list[x + byte_row * WIDTH]
            for bit in range(8):
                y = byte_row * 8 + bit
                idx = y * WIDTH + x
                pixels[idx] = 1 if ((b >> bit) & 1) else 0
    return pixels

# Main page
@app.route("/")
def index():
    return render_template_string("""
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>64x64 editor</title>
<style>
:root { --cell: 10px; }
body { background:#111; color:#ddd; margin:0; display:flex; flex-direction:column; align-items:center; gap:8px; padding:12px; font-family:monospace; }
#grid { display:grid; grid-template-columns: repeat({{w}}, var(--cell)); grid-template-rows: repeat({{h}}, var(--cell)); }
.cell { width:var(--cell); height:var(--cell); border:1px solid #222; box-sizing:border-box; cursor:pointer; }
#controls { display:flex; gap:8px; }
button { font-family:monospace; padding:6px 10px; }
</style>
</head>
<body>
<div id="controls">
<button id="saveBtn">Save</button>
<button id="reloadBtn">Reload</button>
<select id="frameSelector">
{% for i in range(frames_count) %}
<option value="{{i}}">Frame {{i+1}}</option>
{% endfor %}
</select>
</div>

<div id="grid" aria-label="pixel grid"></div>

<script>
const W = {{w}};
const H = {{h}};
let bytes = [];
let pixels = [];

async function loadFromServer(frame=0) {
    const res = await fetch('/data?frame=' + frame);
    const j = await res.json();
    bytes = j.bytes.slice();
    pixels = j.pixels.slice();
    renderGrid();
}

function renderGrid() {
    const grid = document.getElementById('grid');
    grid.innerHTML = '';
    for (let i = 0; i < pixels.length; i++) {
        const x = i % W;
        const y = Math.floor(i / W);
        const byteRow = Math.floor(y / 8);
        const bit = y % 8;
        const bIndex = x + byteRow * W;
        const div = document.createElement('div');
        div.className = 'cell';
        div.style.backgroundColor = pixels[i] ? '#fff' : '#000';
        div.dataset.idx = i;
        div.dataset.bindex = bIndex;
        div.dataset.bit = bit;

        div.addEventListener('click', (e) => {
            const bi = Number(e.currentTarget.dataset.bindex);
            const bt = Number(e.currentTarget.dataset.bit);
            const idx = Number(e.currentTarget.dataset.idx);

            if ((bytes[bi] >> bt) & 1) {
                bytes[bi] &= ~(1 << bt);
                pixels[idx] = 0;
                e.currentTarget.style.backgroundColor = '#000';
            } else {
                bytes[bi] |= (1 << bt);
                pixels[idx] = 1;
                e.currentTarget.style.backgroundColor = '#fff';
            }
        });

        grid.appendChild(div);
    }
}

document.getElementById('saveBtn').addEventListener('click', async () => {
    const frame = document.getElementById('frameSelector').value;
    const res = await fetch(`/save?frame=${frame}`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ bytes })
    });
    const j = await res.json();
    if (!j.ok) console.error('save failed', j);
});

document.getElementById('reloadBtn').addEventListener('click', () => loadFromServer(document.getElementById('frameSelector').value));
document.getElementById('frameSelector').addEventListener('change', (e) => loadFromServer(e.target.value));

loadFromServer();
</script>
</body>
</html>
""", w=WIDTH, h=HEIGHT, frames_count=len(image_frames))

# Provide pixel and byte data
@app.route("/data")
def get_data():
    frame_index = int(request.args.get("frame", 0))
    frame_index = max(0, min(frame_index, len(image_frames)-1))
    pixels = expand_pixels(image_frames[frame_index])
    return jsonify({"pixels": pixels, "bytes": image_frames[frame_index]})

# Save updated bytes
@app.route("/save", methods=["POST"])
def save():
    global image_frames
    payload = request.get_json(force=True)
    new_bytes = payload.get("bytes")
    if not isinstance(new_bytes, list) or len(new_bytes) != BYTES_EXPECTED:
        return jsonify({"ok": False, "error": f"bytes must be list of length {BYTES_EXPECTED}"}), 400

    try:
        new_bytes_int = [int(b) & 0xFF for b in new_bytes]
    except Exception:
        return jsonify({"ok": False, "error": "bytes must be numbers"}), 400

    frame_index = int(request.args.get("frame", 0))
    frame_index = max(0, min(frame_index, len(image_frames)-1))
    image_frames[frame_index][:] = new_bytes_int

    # Print formatted hex array for terminal
    per_line = 16
    print(f"Frame {frame_index} updated:")
    print("    {")
    for i in range(0, BYTES_EXPECTED, per_line):
        chunk = new_bytes_int[i:i+per_line]
        line = "        " + ", ".join(f"0x{b:02x}" for b in chunk) + ("," if i + per_line < BYTES_EXPECTED else "")
        print(line)
    print("    },\n")

    return jsonify({"ok": True})

if __name__ == "__main__":
    app.run(debug=True)

