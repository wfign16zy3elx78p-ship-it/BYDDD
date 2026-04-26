# BYD Seal 2026 Landing Concept

Prototype landing page cinematic với model 3D thật (GLB).

## Cách thay model xe BYD

1. Tạo thư mục `assets/` ở root repo.
2. Copy file model vào `assets/byd-seal.glb`.
3. Mở `index.html` (hoặc chạy local server) để xem.

> Script đang load model bằng `GLTFLoader` tại đường dẫn cố định `assets/byd-seal.glb`.

## Nếu model chưa lên màu đúng

Trong `app.js`, phần `carModel.traverse(...)` đang bắt mesh theo tên/material:

- `paint`, `body` → cho đổi màu theo swatch
- `light`, `headlight`, `lamp` → cho hiệu ứng đèn khi hover

Nếu model của bạn đặt tên khác, đổi lại điều kiện match tên là được.

## Chạy local (khuyến nghị)

Do import module từ CDN, nên chạy bằng local server:

```bash
python3 -m http.server 8080
```

Sau đó mở `http://localhost:8080`.
