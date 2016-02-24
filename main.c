/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2016 devim
 * 
 * LightWebSearch is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LightWebSearch is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

#define UI_FILE "lightwebsearch.ui"

#define BROWSER "epiphany" //or firefox, etc.
#define SEARCH_ENGINE "https://www.duckduckgo.com" //or https://www.google.com

#define ENABLE_BUILD_FROM_STRING 1

static void quit ()
{
	gtk_main_quit ();
}

/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */
    
gboolean on_inputtext_key_press_event (GtkSearchEntry *searchentry, GdkEvent *event, gpointer user_data)
{
	const gchar *query;
	char cmd[300];
	switch (((GdkEventKey*)event)->keyval)
  	{
    	case GDK_KEY_Escape:
    		quit ();
    		break;
    	case GDK_KEY_Return:
    	case GDK_KEY_KP_Enter:
    		query = gtk_entry_get_text((GtkEntry*)searchentry);
    		sprintf (cmd, "nohup %s --new-tab \"%s/?q=%s\" > /dev/null &", BROWSER, SEARCH_ENGINE, (char*)query);
    		system(cmd);
    		quit ();
    		break;    	
    }
    return FALSE;
}

static GtkWidget*
create_window (void)
{
	GtkWidget *window;
	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	#if ENABLE_BUILD_FROM_STRING
	builder = gtk_builder_new_from_string (gladestring, -1);
	#else
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	#endif
	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        if (!window)
        {
                g_critical ("Window widget is missing in file %s.",	UI_FILE);
        }

	g_object_unref (builder);

	
	return window;
}

int
main (int argc, char *argv[])
{
 	GtkWidget *window;
	gtk_init (&argc, &argv);
	window = create_window ();
	gtk_widget_show (window);

	gtk_main ();

	return 0;
}
