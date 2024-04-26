#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>

int main() {
    // Create a temporary event source
    CGEventSourceRef eventSource = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    if (!eventSource) {
        fprintf(stderr, "Failed to create event source\n");
        return 1;
    }
    
    // Create a key down event with the highest possible key code
    CGEventRef event = CGEventCreateKeyboardEvent(eventSource, (CGKeyCode)UINT16_MAX, true);
    if (!event) {
        fprintf(stderr, "Failed to create keyboard event\n");
        CFRelease(eventSource);
        return 1;
    }
    
    // Get the key code from the event
    CGKeyCode maxKeyCode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    
    // Release the event and event source
    CFRelease(event);
    CFRelease(eventSource);
    
    printf("Max Key Code: %d\n", (int)maxKeyCode);
    
    return 0;
}
