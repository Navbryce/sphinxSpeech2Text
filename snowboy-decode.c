#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BILLION  1000000000.0;


int main(void) {
    struct timespec start, end;
    if (getenv("SPEECH_RECOGNITION") == NULL) {
	system("echo Please set the SPEECH_RECOGNITION environment variable to point to the git repository");
	return 1;
    }
    system("export LD_LIBRARY_PATH=/usr/local/lib");
    while (system("python klauba.py") == 0) {
        system("echo Starting to decode...");
        clock_gettime(CLOCK_REALTIME, &start);
        system("\
            pocketsphinx_continuous \
            -infile ./testfiles/raw_recording.wav \
            -remove_noise yes \
            -lm ./corpus/Corpus_V2/1586.lm \
            -dict ./corpus/Corpus_V2/1586.dic \
            2>./output/unwanted-stuff.log | tee ./output/words.txt");
        system("echo Done decoding...");
 //       clock_gettime(CLOCK_REALTIME, &end);
 //       double time_spent = (end.tv_sec - start.tv_sec) +
 //                           (end.tv_nsec - start.tv_nsec) / BILLION;
 //       char *timerOutput = malloc(25);
 //       sprintf(timerOutput, "echo Time Elapsed: %f\n", time_spent);
 //       system(timerOutput);
//        free(timerOutput);
    }
}
