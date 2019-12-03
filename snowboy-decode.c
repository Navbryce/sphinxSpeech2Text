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
            -lm ./corpus/Corpus_V3/100.lm \
            -dict ./corpus/Corpus_V3/100.dic \
            2>./output/unwanted-stuff.log | sudo -i python $SPEECH_RECOGNITION/process-output.py");
        system("echo Done decoding...");
    }
}
