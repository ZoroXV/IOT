import random
import requests
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

mail_settings = {
    "mail_content": 'from python backend',
    "sender_address": 'modifié',
    "sender_pass": 'modifié',
    "receiver_address":'modifié',
    "message": MIMEMultipart()
}

stats = {
    "temperature": 1,
    "humidity": 2,
    "level": 3
}

def setup_mail():
    mail_settings["message"]['From'] = mail_settings["sender_address"]
    mail_settings["message"]['To'] = mail_settings["receiver_address"]
    mail_settings["message"]['Subject'] = '[IOT] trop haut'
    mail_settings["message"].attach(MIMEText(mail_settings["mail_content"], 'plain'))

def get_stats():
    if (stats["level"] > 50):
        send_email()

    return (stats["temperature"], stats["humidity"], stats["level"])

def post_frequency(freq):
    # No idea how this works
    return

def send_email():
    session = smtplib.SMTP('smtp.gmail.com', 587)
    session.starttls()
    session.login(mail_settings["sender_address"], mail_settings["sender_pass"])
    text = mail_settings["message"].as_string()
    session.sendmail(mail_settings["sender_address"], mail_settings["receiver_address"], text)
    session.quit()

def get_stats_mock():
    t = (30.0) * random.random()
    h = (20.0) * random.random()
    l = (10.0) * random.random()

    return (t, h, l)
