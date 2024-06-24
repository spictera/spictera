#include <stdlib.h>
#include <stdio.h>
#include <glib/gi18n.h>
#include <geoclue.h>

/* Commandline options */
static gint timeout = 30; /* seconds */
static GClueAccuracyLevel accuracy_level = GCLUE_ACCURACY_LEVEL_EXACT;
static gint time_threshold;

GClueSimple *simple = NULL;
GClueClient *client = NULL;
GMainLoop *main_loop;

static gboolean on_location_timeout(gpointer user_data)
{
	printf("%s():ENTRY\n",__FUNCTION__);

	g_clear_object (&client);
	g_clear_object (&simple);
	g_main_loop_quit (main_loop);

	printf("%s():LEAVING:return false\n",__FUNCTION__);
	return FALSE;
}

static void print_location(GClueSimple *simple)
{
	GClueLocation *location;
	gdouble altitude, speed, heading;
	GVariant *timestamp;
	GTimeVal tv = { 0 };
	GDateTime *date_time;
	const char *desc;
	gchar *str;

	printf("%s():ENTRY\n",__FUNCTION__);

        printf("%s():gclue_simple_get_location()\n",__FUNCTION__);
	location = gclue_simple_get_location (simple);

        printf("%s():Lattitude: %f°\n", __FUNCTION__, gclue_location_get_latitude (location));
        printf("%s():Lattitude: %f°\n", __FUNCTION__, gclue_location_get_longitude (location));
	printf("%s():Accuracy: %f meters\n", __FUNCTION__,gclue_location_get_accuracy (location));

        printf("%s():gclue_simple_get_altitude()\n",__FUNCTION__);
	altitude = gclue_location_get_altitude(location);
	if(altitude != -G_MAXDOUBLE)
		printf("%s():Altitude: %f meters\n", __FUNCTION__,altitude);

        printf("%s():gclue_simple_get_altitude()\n",__FUNCTION__);
	speed = gclue_location_get_speed(location);
	if(speed >= 0)
		printf("%s():Speed: %f meters/second\n", __FUNCTION__,speed);

        printf("%s():gclue_simple_get_heading()\n",__FUNCTION__);
	heading = gclue_location_get_heading(location);
	if(heading >= 0)
		printf("%s():Heading: %f°\n", __FUNCTION__,heading);

        printf("%s():gclue_simple_get_description()\n",__FUNCTION__);
	desc = gclue_location_get_description(location);
        if(strlen (desc) > 0)
		printf("%s():Description: %s\n", __FUNCTION__,desc);

        printf("%s():gclue_simple_get_timestamp()\n",__FUNCTION__);
	timestamp = gclue_location_get_timestamp(location);
	if (timestamp) 
	{
		g_variant_get(timestamp, "(tt)", &tv.tv_sec, &tv.tv_usec);

		date_time = g_date_time_new_from_timeval_local(&tv);
		str = g_date_time_format(date_time, "%c (%s seconds since the Epoch)");
		g_date_time_unref (date_time);

		printf("%s():Timestamp: %s\n", __FUNCTION__,str);
		g_free (str);
	}
	printf("%s():LEAVING\n",__FUNCTION__);
}

static void on_client_active_notify (GClueClient *client, GParamSpec *pspec, gpointer user_data)
{
	printf("%s():ENTRY\n",__FUNCTION__);

        printf("%s():gclue_get_active()\n",__FUNCTION__);
	if (gclue_client_get_active(client))
        {
		printf("%s():LEAVING\n",__FUNCTION__);
		return;
        }

	printf("%s():Geolocation disabled. Quitting.\n",__FUNCTION__);
	on_location_timeout(NULL);

	printf("%s():LEAVING\n",__FUNCTION__);
}

static void on_simple_ready (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = NULL;

	printf("%s():ENTRY\n",__FUNCTION__);

        printf("%s():gclue_simple_new_finish()\n",__FUNCTION__);
	simple = gclue_simple_new_finish (res, &error);
	if (error != NULL) 
	{
		printf("%s():ERROR:%s\n",__FUNCTION__,error->message);

		g_clear_object (&client);
		g_clear_object (&simple);
		g_main_loop_quit (main_loop);

		printf("%s():LEAVING\n",__FUNCTION__);
		return;
	}

	printf("%s():gclue_simple_get_client()\n",__FUNCTION__);
	client = gclue_simple_get_client(simple);

	g_object_ref(client);
	printf("%s():Client object: %s\n", __FUNCTION__,g_dbus_proxy_get_object_path (G_DBUS_PROXY (client)));
	
	if (time_threshold > 0) 
	{
		gclue_client_set_time_threshold(client, time_threshold);
	}

	print_location (simple);

	g_signal_connect (simple, "notify::location", G_CALLBACK (print_location), NULL);
	g_signal_connect (client, "notify::active", G_CALLBACK (on_client_active_notify), NULL);

	printf("%s():LEAVING\n",__FUNCTION__);
}

int getlocation(void)
{
	GOptionContext *context;

	printf("%s():ENTRY\n",__FUNCTION__);
	g_timeout_add_seconds (timeout, on_location_timeout, NULL);

	printf("%s():gclue_simple_new(%d)\n",__FUNCTION__,accuracy_level);
	gclue_simple_new ("spictera", accuracy_level, NULL, on_simple_ready, NULL);

	main_loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (main_loop);

	printf("%s():LEAVING\n",__FUNCTION__);
	return EXIT_SUCCESS;
}

int main(void)
{
	int rc = getlocation();
	return rc;
}
