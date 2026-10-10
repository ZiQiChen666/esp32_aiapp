// Modern web UI for the ESP32-CAM project.
// Served directly from flash by app_httpd.cpp (index_handler).
#pragma once

const char index_html[] PROGMEM = R"html(<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>ESP32-CAM 网络摄像头</title>
<style>
:root{
  --bg:#0b1220; --panel:#131c2e; --panel-2:#1b2740; --line:#26334d;
  --txt:#e6edf7; --muted:#8fa3c0; --accent:#3b82f6; --accent2:#22d3ee;
  --ok:#22c55e; --danger:#ef4444; --warn:#f59e0b; --radius:16px;
}
*{box-sizing:border-box;-webkit-tap-highlight-color:transparent}
html,body{margin:0;padding:0}
body{
  background:radial-gradient(1200px 600px at 20% -10%,#1e293b 0%,var(--bg) 55%) fixed;
  color:var(--txt);
  font-family:system-ui,-apple-system,"Segoe UI",Roboto,"Microsoft YaHei",sans-serif;
  min-height:100vh; padding:18px clamp(10px,3vw,34px) 60px;
}
h1,h2,h3{margin:0;font-weight:650;letter-spacing:.2px}
a{color:var(--accent2);text-decoration:none}
button,select,input[type=text]{font:inherit}
button{
  cursor:pointer;border:1px solid transparent;border-radius:12px;padding:11px 16px;
  color:#fff;background:#243352;transition:.18s transform,.18s filter,.18s background;
  display:inline-flex;align-items:center;gap:8px;justify-content:center;white-space:nowrap;
}
button:hover{filter:brightness(1.15)}
button:active{transform:translateY(1px)}
button.primary{background:linear-gradient(135deg,var(--accent),#6366f1)}
button.danger{background:linear-gradient(135deg,var(--danger),#b91c1c)}
button.ok{background:linear-gradient(135deg,var(--ok),#15803d)}
button.ghost{background:transparent;border-color:var(--line);color:var(--txt)}
button:disabled{opacity:.5;cursor:not-allowed}
header{
  display:flex;align-items:center;gap:14px;flex-wrap:wrap;
  padding:14px 20px;margin-bottom:20px;border:1px solid var(--line);
  border-radius:var(--radius);background:linear-gradient(180deg,rgba(30,41,59,.9),rgba(19,28,46,.9));
  backdrop-filter:blur(6px);
}
.logo{
  width:42px;height:42px;border-radius:12px;flex:0 0 auto;
  background:linear-gradient(135deg,var(--accent),var(--accent2));
  display:grid;place-items:center;font-size:22px;
}
header .title{font-size:19px}
header .sub{font-size:12px;color:var(--muted)}
header .spacer{flex:1}
.pill{
  font-size:12px;padding:6px 12px;border-radius:999px;border:1px solid var(--line);
  background:var(--panel-2);color:var(--muted);display:inline-flex;align-items:center;gap:7px;
}
.dot{width:9px;height:9px;border-radius:50%;background:var(--muted);box-shadow:0 0 8px currentColor}
.dot.green{background:var(--ok);color:var(--ok)}
.dot.red{background:var(--danger);color:var(--danger)}
.dot.amber{background:var(--warn);color:var(--warn)}
main{display:grid;grid-template-columns:minmax(0,1.35fr) minmax(0,1fr);gap:20px}
@media(max-width:1000px){main{grid-template-columns:1fr}}
.panel{
  border:1px solid var(--line);border-radius:var(--radius);
  background:linear-gradient(180deg,rgba(27,39,64,.85),rgba(19,28,46,.95));
  padding:18px;box-shadow:0 12px 30px rgba(0,0,0,.35);
}
.panel h2{font-size:16px;display:flex;align-items:center;gap:9px}
.panel h2 .ico{color:var(--accent2)}
.video-wrap{
  position:relative;width:100%;aspect-ratio:4/3;margin:14px 0;
  border-radius:14px;overflow:hidden;background:#05080f;border:1px solid var(--line);
}
.video-wrap img{width:100%;height:100%;object-fit:contain;display:block}
#streamOverlay{
  position:absolute;inset:0;display:flex;flex-direction:column;gap:8px;
  align-items:center;justify-content:center;color:var(--muted);font-size:14px;
  background:repeating-linear-gradient(45deg,#0a1120,#0a1120 12px,#0c1626 12px,#0c1626 24px);
}
#recBadge{
  position:absolute;top:12px;left:12px;display:none;align-items:center;gap:7px;
  background:rgba(239,68,68,.92);color:#fff;font-size:12px;font-weight:600;
  padding:6px 12px;border-radius:999px;z-index:4;
}
#recBadge .dot{background:#fff;color:#fff;animation:blink 1s infinite}
@keyframes blink{50%{opacity:.25}}
.controls{display:grid;grid-template-columns:repeat(auto-fit,minmax(140px,1fr));gap:10px}
.controls button{width:100%}
.files-head{display:flex;align-items:center;gap:10px;flex-wrap:wrap;margin-bottom:12px}
.files-head .spacer{flex:1}
.sdbar{font-size:12px;color:var(--muted);margin:2px 2px 12px;display:flex;align-items:center;gap:8px}
.progress{flex:1;height:7px;border-radius:99px;background:#0a1220;overflow:hidden;border:1px solid var(--line)}
.progress>i{display:block;height:100%;background:linear-gradient(90deg,var(--accent),var(--accent2));width:0%}
.table-wrap{max-height:430px;overflow:auto;border:1px solid var(--line);border-radius:12px}
table{width:100%;border-collapse:collapse;font-size:13px}
th,td{padding:10px 12px;text-align:left;border-bottom:1px solid var(--line);vertical-align:middle}
th{position:sticky;top:0;background:#162134;color:var(--muted);font-weight:600;font-size:12px;letter-spacing:.4px;z-index:1}
tbody tr:hover{background:rgba(59,130,246,.08)}
td.name{max-width:220px;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
td.actions{text-align:right;white-space:nowrap}
td.actions button{padding:6px 10px;font-size:12px;border-radius:9px}
.empty{padding:30px;text-align:center;color:var(--muted);font-size:13px}
.settings{margin-top:20px}
.grid-settings{display:grid;grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:14px;margin-top:14px}
.field{display:flex;flex-direction:column;gap:6px}
.field label{font-size:12px;color:var(--muted)}
select,input[type=text]{
  background:#0d1728;color:var(--txt);border:1px solid var(--line);
  border-radius:11px;padding:10px 12px;outline:none;
}
select:focus,input[type=text]:focus{border-color:var(--accent)}
.switch{display:flex;align-items:center;justify-content:space-between;gap:10px;
  background:#0d1728;border:1px solid var(--line);border-radius:11px;padding:9px 12px}
.switch span{font-size:13px}
.switch input{appearance:none;width:44px;height:24px;border-radius:99px;background:#2b3a55;position:relative;transition:.2s;cursor:pointer;flex:0 0 auto}
.switch input:checked{background:var(--accent)}
.switch input::after{content:"";position:absolute;top:3px;left:3px;width:18px;height:18px;border-radius:50%;background:#fff;transition:.2s}
.switch input:checked::after{left:23px}
/* ---- AI panel ---- */
.ai-box{margin-top:14px;border-top:1px solid var(--line);padding-top:14px}
.ai-head{display:flex;gap:10px;align-items:center;flex-wrap:wrap;margin-bottom:10px}
.ai-head h3{font-size:14px;flex:0 0 auto}
.ai-head select{flex:1;min-width:130px}
.ai-head button{padding:9px 14px}
.ai-status{font-size:12px;color:var(--muted);margin-bottom:10px;min-height:16px;line-height:1.5}
.ai-status.busy{color:var(--accent2)}
.ai-status.error{color:var(--danger)}
.ai-results{list-style:none;margin:0;padding:0;display:flex;flex-wrap:wrap;gap:8px}
.ai-results li{background:#0d1728;border:1px solid var(--line);border-radius:10px;padding:6px 10px;font-size:12px;display:flex;gap:8px;align-items:center}
.ai-results .bar{width:46px;height:6px;border-radius:99px;background:#243352;overflow:hidden}
.ai-results .bar>i{display:block;height:100%;background:linear-gradient(90deg,var(--accent),var(--accent2))}
#dangerBanner{position:absolute;left:0;right:0;top:0;padding:10px 14px;z-index:5;display:none;
  background:linear-gradient(90deg,#dc2626,#b91c1c);color:#fff;font-weight:700;font-size:14px;
  text-align:center;letter-spacing:.5px;box-shadow:0 6px 18px rgba(220,38,38,.5);animation:dangerPulse 1s infinite}
@keyframes dangerPulse{50%{opacity:.72}}
#overlay{position:absolute;display:none;pointer-events:none;z-index:3}
.modal{position:fixed;inset:0;background:rgba(3,7,15,.85);display:none;align-items:center;justify-content:center;padding:20px;z-index:50}
.modal.show{display:flex}
.modal-box{background:var(--panel);border:1px solid var(--line);border-radius:var(--radius);padding:16px;max-width:min(860px,95vw)}
.modal-box img{max-width:100%;max-height:70vh;border-radius:10px;display:block;background:#05080f}
.modal-actions{display:flex;gap:10px;justify-content:flex-end;margin-top:12px}
#toast{
  position:fixed;left:50%;bottom:26px;transform:translate(-50%,20px);
  background:#16233a;border:1px solid var(--line);color:var(--txt);
  padding:12px 18px;border-radius:12px;font-size:13px;opacity:0;pointer-events:none;
  transition:.25s;z-index:80;max-width:90vw;box-shadow:0 10px 30px rgba(0,0,0,.5)
}
#toast.show{opacity:1;transform:translate(-50%,0)}
#toast.err{border-color:var(--danger)}
.upload-label{display:inline-flex}
.upload-label input{display:none}
</style>
</head>
<body>
<header>
  <div class="logo">📷</div>
  <div>
    <div class="title">ESP32-CAM 网络摄像头</div>
    <div class="sub">实时预览 · 拍照 · 录像 · SD 卡文件管理</div>
  </div>
  <div class="spacer"></div>
  <span class="pill"><span id="srvDot" class="dot amber"></span><span id="srvText">连接中…</span></span>
  <span class="pill"><span id="sdDot" class="dot"></span><span id="sdText">SD 卡检测中…</span></span>
</header>

<main>
  <section class="panel">
    <h2><span class="ico">🎥</span> 实时视频</h2>
    <div class="video-wrap">
      <img id="stream" crossorigin="anonymous" alt="视频未开启">
      <canvas id="overlay"></canvas>
      <div id="streamOverlay">视频流已关闭<br><small>点击下方“开启视频流”开始预览</small></div>
      <div id="recBadge"><span class="dot"></span> 录制中 <span id="recTime">00:00</span></div>
      <div id="dangerBanner">⚠ 危险：检测到电动车 / 电池，禁止进入电梯！</div>
    </div>
    <div class="controls">
      <button id="btnStream" class="primary">开启视频流</button>
      <button id="btnPhoto" class="ghost">📸 拍照</button>
      <button id="btnSavePhoto" class="ghost">💾 拍照存 SD</button>
      <button id="btnRecord" class="danger">⏺ 开始录制</button>
    </div>

    <div class="ai-box">
      <div class="ai-head">
        <h3>🤖 AI 智能识别</h3>
        <select id="aiTask">
          <option value="object" selected>物体识别</option>
          <option value="insect">虫蛀检测</option>
          <option value="elevator">电梯安全检测</option>
          <option value="fire" disabled>火灾检测（开发中）</option>
          <option value="measure" disabled>2D 物体测量（开发中）</option>
          <option value="face" disabled>人脸检测（开发中）</option>
          <option value="facerec" disabled>人脸识别（开发中）</option>
          <option value="track" disabled>物体追踪（开发中）</option>
        </select>
        <button id="btnDetect" class="primary">识别当前画面</button>
        <button id="btnAuto" class="ghost">连续识别</button>
        <button id="btnSaveDetect" class="ghost">💾 保存标注图</button>
      </div>
      <div id="aiStatus" class="ai-status">就绪 — 点击“识别当前画面”，结果会框选在画面上</div>
      <ul id="aiResults" class="ai-results"></ul>
    </div>
  </section>

  <section class="panel">
    <div class="files-head">
      <h2><span class="ico">🗂️</span> SD 卡文件</h2>
      <div class="spacer"></div>
      <label class="upload-label">
        <button class="ghost" type="button" onclick="this.parentNode.querySelector('input').click()">⬆ 上传</button>
        <input type="file" id="uploadInput">
      </label>
      <button id="btnRefresh" class="primary">刷新</button>
    </div>
    <div class="sdbar">
      <span id="sdUsage">--</span>
      <span class="progress"><i id="sdBar"></i></span>
      <span id="sdFree">--</span>
    </div>
    <div class="table-wrap">
      <table>
        <thead><tr><th>文件名</th><th>大小</th><th>修改时间</th><th style="text-align:right">操作</th></tr></thead>
        <tbody id="fileBody"><tr><td colspan="4" class="empty">正在加载…</td></tr></tbody>
      </table>
    </div>
  </section>
</main>

<section class="panel settings">
  <h2><span class="ico">⚙️</span> 摄像头设置</h2>
  <div class="grid-settings">
    <div class="field">
      <label>分辨率</label>
      <select id="setFramesize">
        <option value="5">QVGA 320×240</option>
        <option value="6">CIF 400×296</option>
        <option value="8">VGA 640×480</option>
        <option value="9">SVGA 800×600</option>
        <option value="10">HD 1280×720</option>
        <option value="11">SXGA 1280×1024</option>
        <option value="12">UXGA 1600×1200</option>
      </select>
    </div>
    <div class="field">
      <label>画质 (越小越好)</label>
      <select id="setQuality"></select>
    </div>
    <div class="field">
      <label>亮度</label>
      <select id="setBrightness"></select>
    </div>
    <div class="field">
      <label>对比度</label>
      <select id="setContrast"></select>
    </div>
    <div class="field">
      <label>饱和度</label>
      <select id="setSaturation"></select>
    </div>
    <div class="field">
      <label>补光灯亮度</label>
      <select id="setLed"></select>
    </div>
    <div class="field">
      <label>图像</label>
      <div class="switch"><span>水平镜像</span><input type="checkbox" id="setHmirror"></div>
    </div>
    <div class="field">
      <label>&nbsp;</label>
      <div class="switch"><span>垂直翻转</span><input type="checkbox" id="setVflip"></div>
    </div>
  </div>
</section>

<div class="modal" id="photoModal">
  <div class="modal-box">
    <img id="photoImg" alt="照片">
    <div class="modal-actions">
      <button class="ghost" onclick="document.getElementById('photoModal').classList.remove('show')">关闭</button>
      <a id="dlPhoto" download="photo.jpg"><button class="primary">下载照片</button></a>
    </div>
  </div>
</div>

<div id="toast"></div>

<script>
const $ = s => document.querySelector(s);
const STREAM_URL = 'http://' + location.hostname + ':81/stream';
let streaming = false, recording = false, recTimer = null, recStart = 0;

function toast(msg, ok = true){
  const t = $('#toast');
  t.textContent = msg;
  t.classList.toggle('err', !ok);
  t.classList.add('show');
  clearTimeout(t._h);
  t._h = setTimeout(() => t.classList.remove('show'), 2600);
}
function fmtSize(n){
  if(n < 1024) return n + ' B';
  if(n < 1048576) return (n/1024).toFixed(1) + ' KB';
  return (n/1048576).toFixed(2) + ' MB';
}
function fmtTime(t){
  if(!t) return '--';
  const d = new Date(t * 1000);
  if(isNaN(d)) return '--';
  return d.toLocaleString();
}

/* ---------------- 视频流 ---------------- */
$('#btnStream').onclick = () => {
  const img = $('#stream'), ov = $('#streamOverlay'), btn = $('#btnStream');
  if(streaming){
    img.src = 'data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==';
    ov.style.display = 'flex';
    ov.innerHTML = '视频流已关闭<br><small>点击下方“开启视频流”开始预览</small>';
    btn.textContent = '开启视频流';
    btn.classList.add('primary'); btn.classList.remove('danger');
    streaming = false;
    const ovl = $('#overlay'); if(ovl) ovl.style.display = 'none';
    const db = $('#dangerBanner'); if(db) db.style.display = 'none';
    lastObjs = [];
  }else{
    img.src = STREAM_URL + '?t=' + Date.now();
    ov.style.display = 'none';
    btn.textContent = '⏹ 关闭视频流';
    btn.classList.remove('primary'); btn.classList.add('danger');
    streaming = true;
  }
};

/* ---------------- 拍照 ---------------- */
$('#btnPhoto').onclick = async () => {
  try{
    const r = await fetch('/capture?t=' + Date.now());
    const b = await r.blob();
    const url = URL.createObjectURL(b);
    $('#photoImg').src = url;
    const a = $('#dlPhoto'); a.href = url; a.download = 'photo_' + Date.now() + '.jpg';
    $('#photoModal').classList.add('show');
  }catch(e){ toast('拍照失败', false); }
};
$('#btnSavePhoto').onclick = async () => {
  try{
    const j = await (await fetch('/save')).json();
    if(j.ok){ toast('已保存到 SD: ' + j.file); loadFiles(); }
    else toast(j.msg || '保存失败', false);
  }catch(e){ toast('保存失败', false); }
};

/* ---------------- 录像 ---------------- */
function tickRec(){
  const s = Math.floor((Date.now() - recStart)/1000);
  $('#recTime').textContent = String(Math.floor(s/60)).padStart(2,'0') + ':' + String(s%60).padStart(2,'0');
}
$('#btnRecord').onclick = async () => {
  const btn = $('#btnRecord');
  btn.disabled = true;
  try{
    if(!recording){
      const j = await (await fetch('/record/start')).json();
      if(j.ok){
        recording = true;
        recStart = Date.now();
        $('#recBadge').style.display = 'flex';
        clearInterval(recTimer); recTimer = setInterval(tickRec, 1000); tickRec();
        btn.textContent = '⏹ 停止录制';
        btn.classList.remove('danger'); btn.classList.add('ok');
        toast('开始录制: ' + j.file);
      }else toast(j.msg || '录制失败', false);
    }else{
      const j = await (await fetch('/record/stop')).json();
      recording = false;
      clearInterval(recTimer);
      $('#recBadge').style.display = 'none';
      btn.textContent = '⏺ 开始录制';
      btn.classList.remove('ok'); btn.classList.add('danger');
      if(j.ok){ toast('录制完成: ' + j.file); loadFiles(); }
      else toast(j.msg || '停止失败', false);
    }
  }catch(e){ toast('操作失败', false); }
  btn.disabled = false;
};

/* ---------------- 文件管理 ---------------- */
async function loadFiles(){
  try{
    const j = await (await fetch('/list')).json();
    const body = $('#fileBody');
    body.innerHTML = '';
    if(!j.ok){
      sdStatus(false, j.msg || 'SD 卡未挂载');
      body.innerHTML = '<tr><td colspan="4" class="empty">SD 卡不可用</td></tr>';
      return;
    }
    sdStatus(true);
    const total = j.total || 0, used = j.used || 0;
    $('#sdUsage').textContent = fmtSize(used) + ' / ' + fmtSize(total);
    $('#sdFree').textContent = '剩余 ' + fmtSize(Math.max(0, total - used));
    $('#sdBar').style.width = total ? (used/total*100).toFixed(1) + '%' : '0%';
    if(!j.files.length){
      body.innerHTML = '<tr><td colspan="4" class="empty">暂无文件</td></tr>';
      return;
    }
    j.files.forEach(f => {
      const tr = document.createElement('tr');
      const tdN = document.createElement('td'); tdN.className = 'name'; tdN.textContent = f.name;
      const tdS = document.createElement('td'); tdS.textContent = fmtSize(f.size);
      const tdT = document.createElement('td'); tdT.textContent = fmtTime(f.time);
      const tdA = document.createElement('td'); tdA.className = 'actions';
      const dl = document.createElement('button'); dl.className='ghost'; dl.textContent='下载';
      dl.onclick = () => { location.href = '/download?file=' + encodeURIComponent(f.name); };
      const rn = document.createElement('button'); rn.className='ghost'; rn.textContent='改名';
      rn.onclick = async () => {
        const nn = prompt('新文件名:', f.name);
        if(!nn || nn === f.name) return;
        const r = await (await fetch('/rename?file=' + encodeURIComponent(f.name) + '&name=' + encodeURIComponent(nn))).json();
        toast(r.ok ? '已重命名' : (r.msg || '重命名失败'), r.ok);
        if(r.ok) loadFiles();
      };
      const del = document.createElement('button'); del.className='danger'; del.textContent='删除';
      del.onclick = async () => {
        if(!confirm('确定删除 ' + f.name + ' ?')) return;
        const r = await (await fetch('/delete?file=' + encodeURIComponent(f.name))).json();
        toast(r.ok ? '已删除' : (r.msg || '删除失败'), r.ok);
        if(r.ok) loadFiles();
      };
      tdA.append(dl, rn, del);
      tr.append(tdN, tdS, tdT, tdA);
      body.appendChild(tr);
    });
  }catch(e){
    $('#fileBody').innerHTML = '<tr><td colspan="4" class="empty">加载失败</td></tr>';
    sdStatus(false, '连接失败');
    $('#srvDot').className = 'dot red'; $('#srvText').textContent = '离线';
  }
}
function sdStatus(ok, msg){
  $('#sdDot').className = 'dot ' + (ok ? 'green' : 'red');
  $('#sdText').textContent = ok ? 'SD 卡已挂载' : (msg || 'SD 卡未挂载');
}
$('#btnRefresh').onclick = loadFiles;

$('#uploadInput').onchange = async e => {
  const file = e.target.files[0];
  if(!file) return;
  toast('正在上传 ' + file.name + ' …');
  try{
    const r = await (await fetch('/upload?file=' + encodeURIComponent(file.name), {method:'POST', body:file})).json();
    toast(r.ok ? '上传成功' : (r.msg || '上传失败'), r.ok);
    if(r.ok) loadFiles();
  }catch(err){ toast('上传失败', false); }
  e.target.value = '';
};

/* ---------------- 设置 ---------------- */
function fillRange(sel, min, max, step=1){
  const el = $(sel); el.innerHTML = '';
  for(let i=min;i<=max;i+=step){
    const o = document.createElement('option'); o.value = i; o.textContent = i; el.appendChild(o);
  }
}
fillRange('#setQuality', 4, 63);
fillRange('#setBrightness', -2, 2);
fillRange('#setContrast', -2, 2);
fillRange('#setSaturation', -2, 2);
fillRange('#setLed', 0, 255, 5);

function setVar(v, val){
  fetch('/control?var=' + v + '&val=' + encodeURIComponent(val)).catch(()=>{});
}
[['#setFramesize','framesize'],['#setQuality','quality'],['#setBrightness','brightness'],
 ['#setContrast','contrast'],['#setSaturation','saturation'],['#setLed','led_intensity']]
.forEach(([sel, name]) => { $(sel).onchange = e => { setVar(name, e.target.value); toast(name + ' = ' + e.target.value); }; });
$('#setHmirror').onchange = e => setVar('hmirror', e.target.checked ? 1 : 0);
$('#setVflip').onchange = e => setVar('vflip', e.target.checked ? 1 : 0);

async function loadStatus(){
  try{
    const s = await (await fetch('/status')).json();
    $('#srvDot').className = 'dot green'; $('#srvText').textContent = '设备在线';
    if(s.framesize !== undefined) $('#setFramesize').value = s.framesize;
    $('#setQuality').value = s.quality;
    $('#setBrightness').value = s.brightness;
    $('#setContrast').value = s.contrast;
    $('#setSaturation').value = s.saturation;
    if(s.led_intensity !== undefined) $('#setLed').value = Math.min(255, Math.round(s.led_intensity / 5) * 5);
    $('#setHmirror').checked = !!s.hmirror;
    $('#setVflip').checked = !!s.vflip;
  }catch(e){
    $('#srvDot').className = 'dot red'; $('#srvText').textContent = '离线';
  }
}

/* ---------------- AI 智能识别 ---------------- */
const AI_OBJECT_PROMPT = `你是物体检测引擎。检测图片中的主要物体，只输出 JSON 数组，不要解释、不要 Markdown。
格式：[{"label":"中文名称","confidence":0.0,"bbox":[x1,y1,x2,y2]}]
bbox 为归一化坐标 0-1（左上 x1,y1，右下 x2,y2），最多 10 个。`;
const AI_INSECT_PROMPT = `你是虫子检测引擎。请判断画面中是否存在虫子（例如米象、谷蠹、蛾/飞蛾、幼虫、蚂蚁、蟑螂、蜘蛛、蝇类等），包括体型很小的虫子。
只输出 JSON 数组，不要解释、不要 Markdown。
格式：[{"label":"虫子中文名称","confidence":0.0,"bbox":[x1,y1,x2,y2]}]
bbox 为归一化坐标 0-1000（左上 x1,y1，右下 x2,y2）。如果没有发现任何虫子，输出 []。`;
const AI_ELEVATOR_PROMPT = `你是电梯安全监控引擎。请判断电梯轿厢内是否出现禁止入内的物品：
电动自行车/电动踏板车/电动摩托、电动车电池、锂电池、铅酸电池、电池包/充电器、电瓶。
只输出 JSON 数组，不要解释、不要 Markdown。
格式：[{"label":"物品中文名称","confidence":0.0,"bbox":[x1,y1,x2,y2]}]
bbox 为归一化坐标 0-1000（左上 x1,y1，右下 x2,y2）。如果画面中没有电动车/电池等违禁物，输出 []。`;
const AI_THRESHOLD = 0.5;
const AI_TASKS = {
  object:   { name:'物体识别',     unit:'个物体',   prompt: AI_OBJECT_PROMPT,   maxW: 416 },
  insect:   { name:'虫蛀检测',     unit:'只虫子',   prompt: AI_INSECT_PROMPT,   maxW: 640 },
  elevator: { name:'电梯安全检测', unit:'个违禁物', prompt: AI_ELEVATOR_PROMPT, maxW: 512, danger: true }
};
let currentTask = 'object';

let aiCfg = { url:'', key:'', model:'', prompt:'', maxW: 416 };
let autoTimer = null, analyzing = false, lastObjs = [], autoOn = false;

function setAiStatus(msg, cls){
  const el = $('#aiStatus');
  el.textContent = msg;
  el.className = 'ai-status' + (cls ? ' ' + cls : '');
}
function currentPrompt(){
  return (AI_TASKS[currentTask] || AI_TASKS.object).prompt;
}
async function loadAiConfig(){
  let server = { url:'', key:'', model:'' };
  try{ server = await (await fetch('/ai/config')).json(); }catch(e){}
  aiCfg.url = server.url || '';
  aiCfg.key = server.key || '';
  aiCfg.model = server.model || '';
  aiCfg.maxW = 416;
}
function liveFrame(){
  const img = $('#stream');
  return (streaming && img.complete && img.naturalWidth > 0) ? img : null;
}
function captureFrame(){
  return fetch('/capture?t=' + Date.now()).then(r => r.blob()).then(b => new Promise((res, rej) => {
    const url = URL.createObjectURL(b);
    const im = new Image();
    im.onload = () => { res(im); setTimeout(() => URL.revokeObjectURL(url), 2000); };
    im.onerror = () => rej(new Error('取帧失败'));
    im.src = url;
  }));
}
// Downscale before upload -> much smaller payload and faster inference
function frameToDataURL(src){
  const maxW = (AI_TASKS[currentTask] && AI_TASKS[currentTask].maxW) || aiCfg.maxW || 416;
  const sw = src.naturalWidth || src.width, sh = src.naturalHeight || src.height;
  const scale = Math.min(1, maxW / sw);
  const w = Math.max(1, Math.round(sw * scale)), h = Math.max(1, Math.round(sh * scale));
  const cv = document.createElement('canvas'); cv.width = w; cv.height = h;
  cv.getContext('2d').drawImage(src, 0, 0, w, h);
  return { dataUrl: cv.toDataURL('image/jpeg', 0.62), w: w, h: h };
}
function parseDetections(text, imgW, imgH){
  let s = String(text || '').trim();
  s = s.replace(/^```[a-zA-Z]*\s*/, '').replace(/```\s*$/, '').trim();
  let arr = null;
  const a = s.indexOf('['), b = s.lastIndexOf(']');
  if(a >= 0 && b > a){
    try{ arr = JSON.parse(s.slice(a, b + 1)); }catch(e){}
  }
  if(!arr){
    const a2 = text.indexOf('{'), b2 = text.lastIndexOf('}');
    if(a2 >= 0 && b2 > a2){
      try{
        const o = JSON.parse(text.slice(a2, b2 + 1));
        arr = o.objects || o.results || o.detections || o.items || [];
      }catch(e){ arr = []; }
    } else arr = [];
  }
  if(!Array.isArray(arr)) arr = arr.objects || arr.results || [];
  const th = AI_THRESHOLD;
  const W = imgW || 1, H = imgH || 1;
  return arr.map(o => {
    let bb = o.bbox || o.box || o.rect || o.rectangle || null;
    if(Array.isArray(bb) && bb.length === 4){
      let v = bb.map(Number);
      const M = Math.max.apply(null, v);
      // Qwen3-VL returns 0-1000 coordinates; some models return 0-1.
      if(M > 1.5) v = v.map(x => x / 1000);
      bb = v.map(x => Math.max(0, Math.min(1, x)));
    } else bb = null;
    const conf = Number(o.confidence != null ? o.confidence : (o.score != null ? o.score : 1));
    const sev = o.severity || o.level || '';
    const label = (o.label || o.name || o.class || o.object || '目标') + (sev ? ' · ' + sev : '');
    return { label: label, confidence: isNaN(conf) ? 1 : conf, bbox: bb };
  }).filter(o => o.confidence >= th);
}
const AI_COLORS = ['#22d3ee','#3b82f6','#f59e0b','#22c55e','#ef4444','#a855f7','#eab308','#ec4899'];
function drawBoxes(ctx, objs, W, H){
  const danger = (AI_TASKS[currentTask] || {}).danger && objs.length > 0;
  const fs = Math.max(12, Math.round(W / 38));
  objs.forEach((o, i) => {
    if(!o.bbox) return;
    const c = danger ? '#ef4444' : AI_COLORS[i % AI_COLORS.length];
    const x = o.bbox[0] * W, y = o.bbox[1] * H;
    const w = (o.bbox[2] - o.bbox[0]) * W, h = (o.bbox[3] - o.bbox[1]) * H;
    ctx.lineWidth = Math.max(2, Math.round(W / 220));
    ctx.strokeStyle = c;
    ctx.strokeRect(x, y, w, h);
    ctx.font = '600 ' + fs + 'px system-ui,-apple-system,sans-serif';
    ctx.textBaseline = 'top';
    const label = o.label + ' ' + Math.round(o.confidence * 100) + '%';
    const tw = ctx.measureText(label).width + 12, th = fs + 8;
    const by = y - th < 0 ? y : y - th;
    ctx.fillStyle = c; ctx.fillRect(x, by, tw, th);
    ctx.fillStyle = '#04121f'; ctx.fillText(label, x + 6, by + 4);
  });
}
function overlayRect(){
  const img = $('#stream');
  const cw = img.clientWidth, ch = img.clientHeight;
  const nw = img.naturalWidth, nh = img.naturalHeight;
  if(!cw || !ch || !nw || !nh) return null;
  const s = Math.min(cw / nw, ch / nh);
  const w = nw * s, h = nh * s;
  return { left: (cw - w) / 2, top: (ch - h) / 2, w: w, h: h };
}
// Transparent canvas that sits exactly over the live video (never hides the stream)
function drawOverlay(objs){
  const cv = $('#overlay');
  const r = overlayRect();
  if(!r){ cv.style.display = 'none'; return; }
  cv.style.left = r.left + 'px'; cv.style.top = r.top + 'px';
  cv.style.width = r.w + 'px'; cv.style.height = r.h + 'px';
  const dpr = window.devicePixelRatio || 1;
  cv.width = Math.max(1, Math.round(r.w * dpr));
  cv.height = Math.max(1, Math.round(r.h * dpr));
  const ctx = cv.getContext('2d');
  ctx.clearRect(0, 0, cv.width, cv.height);
  if(!objs.length){ cv.style.display = 'none'; return; }
  cv.style.display = 'block';
  drawBoxes(ctx, objs, cv.width, cv.height);
}
function renderResults(objs){
  const ul = $('#aiResults'); ul.innerHTML = '';
  if(!objs.length){ ul.innerHTML = '<li>未检测到目标</li>'; return; }
  objs.forEach(o => {
    const li = document.createElement('li');
    const n = document.createElement('span'); n.textContent = o.label;
    const bar = document.createElement('span'); bar.className = 'bar';
    const fill = document.createElement('i'); fill.style.width = Math.round(o.confidence * 100) + '%';
    bar.appendChild(fill);
    const p = document.createElement('span'); p.textContent = Math.round(o.confidence * 100) + '%';
    li.append(n, bar, p); ul.appendChild(li);
  });
}
async function analyze(){
  if(analyzing) return;
  if(!aiCfg.key){ setAiStatus('未配置 API 密钥，请在 ai_config.h 中填写', 'error'); return; }
  analyzing = true;
  setAiStatus('识别中…（视频流保持实时）', 'busy');
  const t0 = performance.now();
  const controller = new AbortController();
  const to = setTimeout(() => controller.abort(), 25000);
  try{
    let src = liveFrame();
    let usedLive = !!src;
    if(!src){
      src = await captureFrame();
      if(!streaming){ $('#stream').src = src.src; $('#streamOverlay').style.display = 'none'; }
    }
    let fr;
    try{
      fr = frameToDataURL(src);
    }catch(err){
      // live frame could not be read (CORS / tainted canvas) -> fall back to /capture
      src = await captureFrame();
      usedLive = false;
      fr = frameToDataURL(src);
    }
    const payload = {
      model: aiCfg.model,
      messages: [{ role:'user', content:[
        { type:'image_url', image_url:{ url: fr.dataUrl } },
        { type:'text', text: currentPrompt() }
      ]}],
      max_tokens: 300,
      temperature: 0
    };
    const resp = await fetch(aiCfg.url, {
      method:'POST',
      headers:{ 'Content-Type':'application/json', 'Authorization':'Bearer ' + aiCfg.key },
      body: JSON.stringify(payload),
      signal: controller.signal
    });
    if(!resp.ok){
      const t = await resp.text();
      throw new Error('HTTP ' + resp.status + ' ' + t.slice(0, 140));
    }
    const j = await resp.json();
    const content = (j.choices && j.choices[0] && j.choices[0].message && j.choices[0].message.content) || '';
    const objs = parseDetections(content, fr.w, fr.h);
    lastObjs = objs;
    drawOverlay(objs);
    renderResults(objs);
    const dt = Math.round(performance.now() - t0);
    const tk = j.usage ? ' · tokens ' + j.usage.total_tokens : '';
    const task = AI_TASKS[currentTask] || AI_TASKS.object;
    const danger = task.danger && objs.length > 0;
    setAiStatus(task.name + '：' + (objs.length ? (danger ? '⚠ 发现 ' : '') + objs.length + ' ' + task.unit : '未发现') + ' · ' + dt + ' ms' + tk + (usedLive ? '' : '（离线抓帧）'), danger ? 'error' : '');
    $('#dangerBanner').style.display = danger ? 'block' : 'none';
  }catch(e){
    if(e && e.name === 'AbortError') setAiStatus('识别超时，已取消', 'error');
    else setAiStatus('识别失败：' + e.message, 'error');
  }finally{
    clearTimeout(to);
    analyzing = false;
  }
}
async function autoLoop(){
  if(!autoOn) return;
  await analyze();
  if(!autoOn) return;
  autoTimer = setTimeout(autoLoop, 400);   // start next only after the previous finished
}
$('#btnDetect').onclick = analyze;
$('#btnSaveDetect').onclick = () => {
  if(!lastObjs.length){ toast('请先识别当前画面', false); return; }
  const src = liveFrame();
  const w = src ? src.naturalWidth : 640, h = src ? src.naturalHeight : 480;
  const cv = document.createElement('canvas'); cv.width = w; cv.height = h;
  const ctx = cv.getContext('2d');
  if(src) ctx.drawImage(src, 0, 0, w, h);
  drawBoxes(ctx, lastObjs, w, h);
  const name = currentTask + '_' + Date.now() + '.jpg';
  cv.toBlob(async blob => {
    try{
      const r = await (await fetch('/upload?file=' + encodeURIComponent(name), { method:'POST', body:blob })).json();
      toast(r.ok ? '已保存到 SD: ' + name : (r.msg || '保存失败'), r.ok);
      if(r.ok) loadFiles();
    }catch(e){ toast('保存失败', false); }
  }, 'image/jpeg', 0.92);
};
$('#btnAuto').onclick = () => {
  const b = $('#btnAuto');
  if(autoOn){
    autoOn = false; clearTimeout(autoTimer); autoTimer = null;
    b.textContent = '连续识别'; b.classList.add('ghost'); b.classList.remove('primary');
    setAiStatus('已停止连续识别');
  }else{
    autoOn = true;
    b.textContent = '⏹ 停止连续'; b.classList.remove('ghost'); b.classList.add('primary');
    toast('已开启连续识别');
    autoLoop();
  }
};
$('#aiTask').onchange = e => {
  if(!AI_TASKS[e.target.value]){ e.target.value = currentTask; return; }
  currentTask = e.target.value;
  lastObjs = [];
  $('#overlay').style.display = 'none';
  $('#aiResults').innerHTML = '';
  $('#dangerBanner').style.display = 'none';
  setAiStatus('已切换到「' + AI_TASKS[currentTask].name + '」，点击“识别当前画面”开始');
};

/* ---------------- 初始化 ---------------- */
loadStatus();
loadFiles();
loadAiConfig();
window.addEventListener('resize', () => { if(lastObjs.length) drawOverlay(lastObjs); });
$('#stream').addEventListener('load', () => { if(lastObjs.length) drawOverlay(lastObjs); });
setInterval(loadFiles, 15000);
setInterval(loadStatus, 30000);
</script>
</body>
</html>
)html";
