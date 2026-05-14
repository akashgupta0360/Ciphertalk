# CipherTalk

Lightweight cybersecurity playground for encrypting and decrypting messages.

```
ciphertalk/
├── frontend/        # Pure HTML + CSS + JS — open index.html in a browser
│   ├── index.html
│   ├── styles.css
│   └── script.js
└── backend/         # C implementation + optional CGI wrapper
    ├── cipher.c
    ├── cipher_cgi.c
    └── README.md
```

## Run the frontend

Just open `frontend/index.html` in any modern browser. The Caesar cipher runs
entirely in JavaScript — no server required.

Or serve it locally:

```bash
cd frontend
python3 -m http.server 5500
# visit http://localhost:5500
```

## Run the C backend

See [`backend/README.md`](backend/README.md) for compile + run instructions.
Quick version:

```bash
cd backend
gcc -O2 -Wall -o cipher cipher.c
./cipher encrypt 3 "Hello, World!"   # Khoor, Zruog!
```

## Connect frontend ↔ backend (optional)

1. Build & serve the CGI binary (see backend README).
2. Open `frontend/script.js` and set `USE_BACKEND = true`.
3. Reload the page — Encrypt/Decrypt now call the C binary over HTTP.
