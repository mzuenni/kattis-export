#include "validation.h"

// This program will be called as
// answer_validator input < ans
//
// You should verify the grammar of the answer file.
// See input_validator.cpp for information on how to use the Validator class.
// Furthermore you should check simple properties of the answer.

// TODO: Remove these comments, and summarize your answer validator.

int main(int argc, char *argv[]) {
    // Set up the input and answer streams.
    std::ifstream in(argv[1]);
    AnswerValidator v(argc, argv);

    int input;
    in >> input;
    v.test_strings({"yes", "no"}, "ans");
    v.newline();
}
