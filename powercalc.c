#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static GtkWidget *display;  // Display area for the calculator

// Function to update the display
void update_display(const char *text) {
    gtk_entry_set_text(GTK_ENTRY(display), text);
}

// Function to handle button clicks
void button_click(GtkWidget *button, gpointer user_data) {
    const gchar *label = gtk_button_get_label(GTK_BUTTON(button));
    const gchar *current_text = gtk_entry_get_text(GTK_ENTRY(display));
    gchar *new_text;

    // Handle the case for the equals button (calculation)
    if (g_strcmp0(label, "=") == 0) {
        // Perform the calculation
        // For simplicity, we use `system()` to invoke a bash calculator command with bc supporting decimals.
        gchar *cmd = g_strdup_printf("echo '%s' | bc -l", current_text);
        FILE *fp = popen(cmd, "r");
        if (fp == NULL) {
            update_display("Error");
        } else {
            char result[100];
            fgets(result, sizeof(result), fp);
            update_display(result);
            fclose(fp);
        }
        g_free(cmd);
    } else if (g_strcmp0(label, "C") == 0) {
        // Clear the display
        update_display("");
    } else {
        // Append the button's label to the current display
        new_text = g_strdup_printf("%s%s", current_text, label);
        update_display(new_text);
        g_free(new_text);
    }
}

// Create the calculator window
GtkWidget* create_calculator() {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    const gchar *buttons[5][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"C", "0", ".", "="},
        {"(", ")", "", ""}
    };

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PowerCalc");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create the display at the top
    display = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), display, 0, 0, 4, 1);
    gtk_entry_set_text(GTK_ENTRY(display), "");
    gtk_widget_set_sensitive(display, FALSE);

    // Create buttons and attach to the grid
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (buttons[i][j][0] != '\0') {
                button = gtk_button_new_with_label(buttons[i][j]);
                g_signal_connect(button, "clicked", G_CALLBACK(button_click), NULL);
                gtk_grid_attach(GTK_GRID(grid), button, j, i + 1, 1, 1);
            }
        }
    }

    return window;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *calculator_window = create_calculator();

    gtk_widget_show_all(calculator_window);

    gtk_main();

    return 0;
}

