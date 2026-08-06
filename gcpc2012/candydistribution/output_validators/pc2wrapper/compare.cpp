/* Adapted to kattis format
   https://clics.ecs.baylor.edu/index.php/Output_validator
*/
/*
   This program is a compare wrapper-script for 'test_solution.sh'.
   See that script for syntax and more info. This program is written to
   comply with the ICPC Validator Interface Standard as described in
   http://www.ecs.csus.edu/pc2/doc/valistandard.html.
   
   Usage: compare <testdata.in> <program.out> <testdata.out> <result.xml> <diff.out>

   <testdata.in>   File containing testdata input.
   <program.out>   File containing the program output.
   <testdata.out>  File containing the correct output.
   <result.xml>    File containing an XML document describing the result.
   <diff.out>      File to write program/correct output differences to.

   Exits successfully except when an internal error occurs. Program
   output is considered correct when diff.out is empty (if specified)
   and exitcode is zero.

   Output format of differences:

   - First a line stating from which line differences were found.
   - Then all lines from that line until end of both <program.out> and
     <testdata.out> formatted as
	 '<PROGRAM LINE>' X '<TESTDATA LINE>'
	 The left and right sides are aligned and ending quote (') is
     replaced by an underscore (_) if the line is truncated. The
     middle 'X' is one of the following characters:
	 = both lines are identical
	 ! the lines are different
	 < left contains additional lines not present right
	 > vice versa
     $ only end-of-lines characters differ (e.g. LF vs. CR+LF); note
       that only LF is considered to begin a newline and all CR
       characters are stripped.
	 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

#define MAXLINELEN 65536

extern int errno;
const int exit_failure = -1;
const size_t maxprintlen = 80;

typedef long long ll;

pair<ll, pair<ll, ll> > eea(ll a, ll b) {
    if (b == 0) return make_pair(a, make_pair(1, 0));
    pair<ll, pair<ll, ll> > p = eea(b, a % b);
    ll s = p.second.first, t = p.second.second;
    return make_pair(p.first, make_pair(t, s - t * (a / b)));
}


/* filenames of commandline arguments */
char *testin, *testout, *progout, *result, *diffout;
char *progname;

void error(int errnum, const char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	
	fprintf(stderr,"%s",progname);
	
	if ( format!=NULL ) {
		fprintf(stderr,": ");
		vfprintf(stderr,format,ap);
	}
	if ( errnum!=0 ) {
		fprintf(stderr,": %s",strerror(errnum));
	}
	if ( format==NULL && errnum==0 ) {
		fprintf(stderr,": unknown error");
	}
	
	fprintf(stderr,"\nTry `%s --help' for more information.\n",progname);
	va_end(ap);
	
	exit(exit_failure);
}

/* Write an XML result file with result message */
void writeresult(const char *msg)
{
	FILE *resultfile;
	
	if (!(resultfile = fopen(result, "w"))) {
		error(errno, "cannot open '%s'", result);
	}

	fprintf(resultfile, "<?xml version=\"1.0\"?>\n");
	fprintf(resultfile, "<!DOCTYPE result [\n");
	fprintf(resultfile, "  <!ELEMENT result (#PCDATA)>\n");
	fprintf(resultfile, "  <!ATTLIST result outcome CDATA #REQUIRED>\n");
	fprintf(resultfile, "]>\n");
	fprintf(resultfile, "<result outcome=\"%s\">%s</result>\n", msg, msg);

	fclose(resultfile);
}

bool
isnum(char *s) {
	if (*s == '\n') {
		return true;
	}
	if (*s == '\0') {
		return true;
	}
	if (!isdigit(*s)) {
		return false;
	}
	return isnum(s+1);
}

int main(int argc, char **argv)
{
	FILE *diffoutfile;
	FILE *obtained, *expected, *inputFile;

	int diff = 0;
	char *obtainedPtr, *expectedPtr, *inputPointer;
	char obtainedLine[MAXLINELEN], expectedLine[MAXLINELEN], inputLine[MAXLINELEN];
	
	// read arguments
	progname = argv[0];
	if (argc - 1 < 5) {
		error(0, "not enough arguments: %d given, 5 required", argc - 1);
	}
	if (argc - 1 > 5) {
		error(0, "too many arguments: %d given, max. 5 accepted", argc - 1);
	}
	testin  = argv[1];
	progout = argv[2];
	testout = argv[3];
	result  = argv[4];
	diffout = argv[5];

	// open files
	if ((diffoutfile = fopen(diffout, "w")) == NULL) {
		error(errno, "opening file '%s'", diffout);
	}
	if ((obtained = fopen(progout, "r")) == NULL) {
		error(errno, "opening file '%s'", progout);
	}
	if ((expected = fopen(testout, "r")) == NULL) {
		error(errno, "opening file '%s'", testout);
	}
	if ((inputFile = fopen(testin, "r")) == NULL) {
		error(errno, "opening file '%s'", testin);
	}

	int numCases;
	inputPointer = fgets(inputLine, MAXLINELEN, inputFile);
	sscanf(inputPointer, "%d", &numCases);

	for (int c = 0; c < numCases; c++) {
		long long K, C;
		inputPointer = fgets(inputLine, MAXLINELEN, inputFile);
		if (inputPointer == NULL) {
			fprintf(diffoutfile, "inputfile ended early after %d cases\n", c);
			diff++;
			break;
		}
		sscanf(inputPointer, "%lld%lld", &K, &C);
		pair<ll, pair<ll, ll> > extEuclid = eea(C, K);

		obtainedPtr = fgets(obtainedLine, MAXLINELEN, obtained);
		if (obtainedPtr == NULL) {
			fprintf(diffoutfile, "obtained file ended early after %d cases\n", c);
			diff++;
			break;
		}
		if (C != 1 && K != 1 && extEuclid.first != 1) {
			if (strcmp(obtainedLine, "IMPOSSIBLE\n") != 0) {
				fprintf(diffoutfile, "%lld %lld should be impossible but answer was %s\n", K, C, obtainedLine);
				diff++;
			}
		} else if (strlen(obtainedLine) > 11) {
			fprintf(diffoutfile, "too long string for %lld, %lld: %s", K, C, obtainedLine);
			diff++;
		} else if (!isnum(obtainedLine)) {
			fprintf(diffoutfile, "no number for %lld, %lld: %s", K, C, obtainedLine);
			diff++;
		} else {
			ll inverse = (extEuclid.second.first + K) % K;
			ll res = atoll(obtainedLine);
			if (res > 1000000000) {
				fprintf(diffoutfile, "answer to %lld %lld too high: %s\n", K, C, obtainedLine);
				diff++;
			} else {
                if (res * C <= K) {
                    // There must be at least K+1 candies under all
                    // circumstances (regardless of K).
					fprintf(diffoutfile, "not enough candies for %lld %lld with #bags == %s\n", K, C, obtainedLine);
                    diff++;
                } else if ((K > 1) and ((res * C) % K != 1LL)) {
                    // If there is one kid (K == 1), then any number of candies
                    // >= 2 will do (and we've already established that there
                    // are enough). But if K > 1, then there must be enough so
                    // that every kid gets one, plus one left over.
					fprintf(diffoutfile, "wrong rest for %lld %lld with #bags == %lld and rest=%lld\n", K, C, res, (res * C) % K);
                    diff++;
                }
			}
		}
	}

	if (diff > 0) {
		writeresult("Wrong Answer");
	} else {
		writeresult("Accepted");
	}
	
	fclose(inputFile);
	fclose(obtained);
	fclose(expected);
	fclose(diffoutfile);
	
	return 0;
}
