#include <stdio.h>
#include <stdlib.h>
#include <vorbis/vorbisfile.h>
#include <alsa/asoundlib.h>
#include "OGG.H"
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

char *buffer;
static char *device = "default";

bool c = true; 

int playSound(char *fname)
{
    c = true;
    buffer = (char *) malloc(4096);
    int err;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;

    if((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0))
            < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }
    if((err = snd_pcm_set_params(handle, SND_PCM_FORMAT_S16_LE,
            SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000))
            < 0) { /* 0.5sec */
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    OggVorbis_File vf;
    int eof = 0;
    int current_section;

    err = ov_fopen(fname, &vf);
    if(err != 0) {
        perror("Error opening file");
    } else {
        vorbis_info *vi = ov_info(&vf, -1);
        //fprintf(stderr, "Bitstream is %d channel, %ldHz\n",
        //        vi->channels, vi->rate);
        //fprintf(stderr, "Encoded by: %s\n\n",
        //        ov_comment(&vf, -1)->vendor);

        while(!eof && c) {
            long ret = ov_read(&vf, buffer, 4096, 0, 2, 1,
                    &current_section);
            if(ret == 0) {
                /* EOF */
                eof = 1;
            } else if(ret < 0) {
                /* error in the stream. */
            } else {
                frames = snd_pcm_writei(handle, buffer, ret/4);
                if(frames < 0)
                    frames = snd_pcm_recover(handle, frames,
                            0);
                if(frames < 0) {
                   // printf("snd_pcm_writei failed: %s\n",
                   //         snd_strerror(err));
                    break;
                }
               // if(frames > 0 && frames < 4096)
                    //printf("Short write (expected %li, wrote %li)\n",
                    //        ret, frames);
            }
        }
        ov_clear(&vf);
    }

    snd_pcm_close(handle);

    return (0);
}

void stopSound() {
    c = false;
}

void *playSoundNoArgs(void * t) {
    return (void*)playSound((char*)t);
}

void playSoundInNewThread(char *fname) {\
    pthread_t newThread;
    pthread_create(&newThread, NULL, playSoundNoArgs, fname);
}