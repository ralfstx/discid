/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2006 Matthias Friedrich
   Copyright (C) 2015 Ralf Sternberg

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------------- */
#include <stdio.h>
#include <discid/discid.h>

#ifndef DISCID_HAVE_SPARSE_READ
#define discid_read_sparse(disc, dev, i) discid_read(disc, dev)
#endif

/*
 * Usage: discid [<device>]
 */
int main(int argc, char *argv[]) {
	DiscId *disc = discid_new();
	int i;
	char *device = NULL;
	/* If we have an argument, use it as the device name */
	if (argc > 1) {
		device = argv[1];
	}
	/* read the disc in the specified (or default) disc drive */
	if (discid_read_sparse(disc, device, 0) == 0) {
		fprintf(stderr, "Error: %s\n", discid_get_error_msg(disc));
		return 1;
	}
	printf("First Track: %d\n", discid_get_first_track_num(disc));
	printf("Last Track: %d\n", discid_get_last_track_num(disc));
	printf("Sectors: %d\n", discid_get_sectors(disc));
	for (i = discid_get_first_track_num(disc); i <= discid_get_last_track_num(disc); i++) {
		printf("Track %-2d: %8d %8d\n", i, discid_get_track_offset(disc, i), discid_get_track_length(disc, i));
	}
	printf("FreeDB ID: %s\n", discid_get_freedb_id(disc));
	printf("MusicBrainz ID: %s\n", discid_get_id(disc));
	printf("MusicBrainz URL: %s\n", discid_get_submission_url(disc));
	discid_free(disc);
	return 0;
}
