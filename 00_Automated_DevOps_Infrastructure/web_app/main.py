import psycopg2
import time
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
import uvicorn

app = FastAPI()

DB_CONF = {
    "host": "db",
    "database": "monitoring_db",
    "user": "user_devops",
    "password": "password123"
}

ALL_REQUESTS = []
LIMIT_REQUESTS = 10
LIMIT_WINDOW = 5
LAST_DB_LOG_TIME = 0

@app.get("/metrics", response_class=HTMLResponse)
def get_metrics(request: Request):
    global ALL_REQUESTS, LAST_DB_LOG_TIME
    current_time = time.time()

    ALL_REQUESTS = [t for t in ALL_REQUESTS if current_time - t < LIMIT_WINDOW]
    ALL_REQUESTS.append(current_time)

    if len(ALL_REQUESTS) > LIMIT_REQUESTS:
        if current_time - LAST_DB_LOG_TIME > 10:
            try:
                conn = psycopg2.connect(**DB_CONF)
                cur = conn.cursor()
                cur.execute("INSERT INTO ram_alerts (ram_usage, cpu_usage, hdd_usage, message) VALUES (%s, %s, %s, %s);",
                            (99.9, 99.9, 99.9, "🚨 КИБЕРАТАКА! DDoS ОТРЕЖЕН!"))
                conn.commit()
                cur.close()
                conn.close()
                LAST_DB_LOG_TIME = current_time
            except: pass
        return HTMLResponse(content="<h1 style='color:red; text-align:center;'>🛑 403 FORBIDDEN: DDoS PROTECTED</h1>", status_code=403)

    try:
        conn = psycopg2.connect(**DB_CONF)
        cur = conn.cursor()
        cur.execute("SELECT id, alert_time, ram_usage, cpu_usage, hdd_usage, message FROM ram_alerts ORDER BY alert_time DESC LIMIT 20;")
        data = cur.fetchall()
        cur.close()
        conn.close()

        table_rows = ""
        for row in data:
            ram_val, cpu_val, hdd_val, msg = row[2] or 0, row[3] or 0, row[4] or 0, row[5] or ""
            
            ram_alert = "style='color: #f38ba8; font-weight: bold;'" if ram_val > 80 else ""
            cpu_alert = "style='color: #fab387; font-weight: bold;'" if cpu_val > 80 else ""
            hdd_alert = "style='color: #89b4fa; font-weight: bold;'" if hdd_val > 80 else ""
            is_attack = "style='background-color: #313244; border-left: 5px solid #f38ba8;'" if "КИБЕРАТАКА" in str(msg) else ""

            table_rows += f"""
            <tr {is_attack}>
                <td>{row[0]}</td>
                <td>{row[1]}</td>
                <td {ram_alert}>{ram_val}%</td>
                <td {cpu_alert}>{cpu_val}%</td>
                <td {hdd_alert}>{hdd_val}%</td>
                <td>{msg}</td>
            </tr>
            """

        html_content = f"""
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <title>DevOps Dashboard</title>
            <style>
                body {{ font-family: sans-serif; background-color: #1e1e2e; color: #cdd6f4; padding: 20px; }}
                h1 {{ color: #f5c2e7; text-align: center; }}
                table {{ width: 100%; border-collapse: collapse; background: #313244; border-radius: 10px; overflow: hidden; }}
                th {{ background: #11111b; color: #a6e3a1; padding: 15px; text-transform: uppercase; }}
                td {{ padding: 12px; text-align: center; border-bottom: 1px solid #45475a; }}
                tr:hover {{ background: #45475a; }}
            </style>
        </head>
        <body>
            <h1>📊 DevOps Real-time Monitoring</h1>
            <table>
                <thead>
                    <tr><th>ID</th><th>Время</th><th>RAM</th><th>CPU</th><th>HDD</th><th>Статус</th></tr>
                </thead>
                <tbody>{table_rows}</tbody>
            </table>
        </body>
        </html>
        """
        return HTMLResponse(content=html_content)
    except Exception as e:
        return HTMLResponse(content=f"<h1>Error: {str(e)}</h1>", status_code=500)

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
