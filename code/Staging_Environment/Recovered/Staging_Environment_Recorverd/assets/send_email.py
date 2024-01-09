# script.py

import argparse
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

def send_email(sender_email, sender_password, recipient, body):
    try:
        # Create an SMTP connection
        smtp_server = "smtp.outlook.com"  # Use your email service's SMTP server
        smtp_port = 587  # Use the appropriate port for your email service (e.g., 587 for TLS)
        server = smtplib.SMTP(smtp_server, smtp_port)
        server.starttls()
        server.login(sender_email, sender_password)

        # Create the email message
        msg = MIMEMultipart()
        msg['From'] = sender_email
        msg['To'] = recipient
        msg['Subject'] = "Your Subject Here"

        msg.attach(MIMEText(body, 'plain'))

        # Send the email
        server.sendmail(sender_email, recipient, msg.as_string())
        print("Email sent successfully")

        # Close the SMTP connection
        server.quit()
    except Exception as e:
        print(f"Failed to send email: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Send an email from C++")
    parser.add_argument("recipient", help="Recipient's email address")

    args = parser.parse_args()
    sender_email = "scrummy1.0@outlook.com"  # Replace with your sender's email address
    sender_password = "SoftwareProject1234"  # Replace with your sender's email password
    email_body = "Hello, this is the email body."  # You can set the email body as needed

    send_email(sender_email, sender_password, args.recipient, email_body)
