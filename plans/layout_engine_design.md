# Layout Engine Design

## Overview
The goal is to create a lightweight layout engine and widget system inspired by toolkits like Tk and Qt. The system should handle basic layout tasks such as centering, alignment, and dynamic resizing, without the complexity of full feature parity.

## Components

### Layout Manager
The layout manager is responsible for managing the overall layout of UI elements. It maintains a list of widgets and their positions, and handles rendering and resizing.

**Key Features:**
- Manages a list of widgets
- Handles rendering of all widgets
- Supports dynamic resizing

### Widget
The base class for all UI elements. Each widget has a position, size, and a render function.

**Key Features:**
- Position (x, y)
- Size (width, height)
- Render function
- Data pointer for widget-specific data

### Text Widget
A widget for displaying text.

**Key Features:**
- Text content
- Color
- Font size
- Font path

### Button Widget
A widget for creating clickable buttons.

**Key Features:**
- Text content
- Color
- Background color
- Font size
- Font path
- Click handler

### Container Widget
A widget that can contain other widgets and manage their layout.

**Key Features:**
- List of child widgets
- Layout management for children

## Integration with Rendering Logic

The rendering logic in `src/demo/linux/sdl_wrapper.c` will be updated to use the new layout engine and widget system. The `render_sdl` function will be modified to use the layout manager to render the widgets.

### Steps for Integration
1. **Create Layout Manager**: Initialize the layout manager with the window dimensions.
2. **Add Widgets**: Create widgets (e.g., text widget for the message) and add them to the layout manager.
3. **Render Layout**: Use the layout manager to render all widgets.
4. **Handle Resizing**: Update the layout manager when the window is resized.

## Example Usage

```c
// Initialize the layout manager
LayoutManager* layout = create_layout_manager(window_width, window_height);

// Create a text widget for the message
Widget* message_widget = create_text_widget(
    "Dragon Raiders, powered by the Funconium Engine",
    (SDL_Color){255, 255, 255, 255},
    36,
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
);

// Add the widget to the layout manager
add_widget_to_layout(layout, message_widget);

// Render the layout
render_layout(layout, renderer);

// Free the layout manager
free_layout_manager(layout);
```

## Implementation Details

### Layout Manager
The layout manager will be responsible for:
- Storing the list of widgets
- Calculating the positions of widgets based on the layout
- Rendering all widgets

### Widget
Each widget will have:
- A position (x, y)
- A size (width, height)
- A render function that takes the widget and a renderer
- A data pointer for widget-specific data
- A function to free the widget-specific data

### Text Widget
The text widget will:
- Store the text content, color, font size, and font path
- Render the text using SDL_ttf
- Handle dynamic resizing and centering

### Button Widget
The button widget will:
- Store the text content, color, background color, font size, font path, and click handler
- Render the button using SDL_ttf and SDL
- Handle click events

### Container Widget
The container widget will:
- Store a list of child widgets
- Manage the layout of child widgets
- Render all child widgets

## Next Steps
1. Implement the layout engine and widget system in C.
2. Update the rendering logic to use the new layout engine.
3. Test the changes to ensure the message is centered and visible in all scenarios.