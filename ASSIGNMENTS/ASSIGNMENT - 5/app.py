import os
import time
from flask import Flask, jsonify

app = Flask(__name__)
START = time.time()

# Small in-memory result set used for benchmarking (no database needed)
RESULTS = {
    "192425093": {"name": "Galla Sai Siddartha", "gpa": 8.9, "status": "PASS"},
    "192425094": {"name": "Sample Student A", "gpa": 7.6, "status": "PASS"},
}


@app.route("/")
def home():
    return jsonify(service="result-portal", message="University Result Portal")


@app.route("/health")
def health():
    return jsonify(status="ok", uptime_s=round(time.time() - START, 1))


@app.route("/result/<reg_no>")
def result(reg_no):
    data = RESULTS.get(reg_no)
    if data is None:
        return jsonify(error="register number not found"), 404
    return jsonify(register_no=reg_no, **data)


@app.route("/db-check")
def db_check():
    url = os.environ.get("DATABASE_URL")
    if not url:
        return jsonify(database="not configured"), 200
    import psycopg2
    try:
        conn = psycopg2.connect(url, connect_timeout=3)
        conn.close()
        return jsonify(database="reachable")
    except Exception as exc:
        return jsonify(database="unreachable", detail=str(exc)), 503


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000)
