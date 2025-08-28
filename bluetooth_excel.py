import serial
import xlwings as xw

# CONFIGURAÇÕES:
COM_PORT = 'COM10'     # Troque pela porta COM do seu módulo HC-05
BAUD_RATE = 9600

# Conectar à porta serial
try:
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    print(f"[OK] Conectado à {COM_PORT} a {BAUD_RATE} bps")
except Exception as e:
    print(f"[ERRO] Falha ao conectar na porta {COM_PORT}:\n{e}")
    exit()

# Conectar ao Excel
try:
    wb = xw.apps.active.books[0]  # Primeira planilha aberta no Excel
    sht = wb.sheets[0]            # Primeira aba
    sht.range("A3:C3").value = ["Sensor 1", "Sensor 2", "Sensor 3"]
    print("[OK] Planilha conectada")
except Exception as e:
    print(f"[ERRO] Não foi possível acessar a planilha:\n{e}")
    ser.close()
    exit()

# Loop principal
print("[INICIADO] Pressione Ctrl+C para parar")
try:
    while True:
        linha = ser.readline().decode().strip()
        if linha:
            partes = linha.split(",")
            if len(partes) == 3:
                print(f"Recebido: {partes}")
                sht.range("A4").value = partes[0]
                sht.range("B4").value = partes[1]
                sht.range("C4").value = partes[2]
except KeyboardInterrupt:
    print("\n[ENCERRADO PELO USUÁRIO]")
finally:
    ser.close()
    print("[OK] Porta serial fechada.")

#Prompt:python bluetooth_excel.py
