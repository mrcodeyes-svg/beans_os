import keyboard

print("Listening for keys... Press 'ESC' to stop.")

def on_key_event(event):
    # 'down' means the key was pressed (the Make code event)
    if event.event_type == 'down':
        print(f"Key: {event.name:<10} | Make Code (Scancode): {event.scan_code}")

# Hook into all global keyboard events
keyboard.hook(on_key_event)

# Keep the script running until you press Escape
keyboard.wait('esc')
