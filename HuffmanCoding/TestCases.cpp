
void testSimple() {

    string passage = "AAAABBBCCCDDEEF";
    map<char,int> expectedCounts = { {'A', 4}, {'B', 3}, {'C', 3}, {'D',2}, {'E',2}, {'F',1} };
    map<char,BitSet> expectedCodes = { {'A',BitSet("10")},{'B',BitSet("111")},
                                       {'C',BitSet("00")},{'D',BitSet("011")},
                                       {'E',BitSet("110")},{'F',BitSet("010")}};

    map<char,BitSet> expectedCanonical = { {'A',BitSet("00")},{'B',BitSet("100")},
                                           {'C',BitSet("01")},{'D',BitSet("101")},
                                           {'E',BitSet("110")},{'F',BitSet("111")}};

    //BitSet expectedTextEncoding("10101010111111111000000011011110110010");   // not canonical
    BitSet expectedTextEncoding("00000000100100100010101101101110110111");   // canonical

    processTextAndEvaluate(passage, expectedCounts, expectedCodes, expectedCanonical, expectedTextEncoding);
}

int testCases() {
    std::cout << "this" " is"            " all"
    " one"
    " string" << endl;
    testSimple();
    return 0;
}