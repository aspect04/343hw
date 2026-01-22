#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

namespace myFlags {
    uint32_t ITS_NOT_YOU_ITS_ME = 1;
    uint32_t I_NEED_TO_FOCUS_ON_MYSELF = 2;
    uint32_t THIS_IS_BETTER_FOR_EVERYONE = 4;
    uint32_t I_DONT_DESERVE_YOU_NEVER_HAVE = 8;
    uint32_t ESCORT_OUT_IMMEDIATE = 16;
    uint32_t ZAP_WITH_LAZER = 32;
};

void terminate(const string &name, const uint32_t flags) {
    cout << "Sorry " << name << ", ";
    if (flags & myFlags::ITS_NOT_YOU_ITS_ME) {
        cout << "ITS_NOT_YOU_ITS_ME ";
    }
    if (flags & myFlags::I_NEED_TO_FOCUS_ON_MYSELF) {
        cout << "I_NEED_TO_FOCUS_ON_MYSELF ";
    }
    if (flags & myFlags::THIS_IS_BETTER_FOR_EVERYONE) {
        cout << "THIS_IS_BETTER_FOR_EVERYONE ";
    }
    if (flags & myFlags::I_DONT_DESERVE_YOU_NEVER_HAVE) {
        cout << "I_DONT_DESERVE_YOU_NEVER_HAVE ";
    }
    if (flags & myFlags::ESCORT_OUT_IMMEDIATE) {
        cout << "ESCORT_OUT_IMMEDIATE ";
    }
    if (flags & myFlags::ZAP_WITH_LAZER) {
        cout << "ZAP_WITH_LAZER";
    }
    cout << endl;
}
int main() {

    terminate("JoJo", myFlags::ITS_NOT_YOU_ITS_ME | myFlags::I_NEED_TO_FOCUS_ON_MYSELF | myFlags::THIS_IS_BETTER_FOR_EVERYONE);
    terminate("JoJo", myFlags::ITS_NOT_YOU_ITS_ME | myFlags::ITS_NOT_YOU_ITS_ME | myFlags::I_DONT_DESERVE_YOU_NEVER_HAVE);
    terminate("JoJo", myFlags::ITS_NOT_YOU_ITS_ME | myFlags::I_DONT_DESERVE_YOU_NEVER_HAVE | myFlags::ZAP_WITH_LAZER | myFlags::ESCORT_OUT_IMMEDIATE);
    terminate("JoJo", myFlags::ITS_NOT_YOU_ITS_ME | myFlags::I_NEED_TO_FOCUS_ON_MYSELF | myFlags::ZAP_WITH_LAZER | myFlags::ESCORT_OUT_IMMEDIATE);
    terminate("JoJo", myFlags::ITS_NOT_YOU_ITS_ME | myFlags::I_DONT_DESERVE_YOU_NEVER_HAVE | myFlags::I_NEED_TO_FOCUS_ON_MYSELF | myFlags::THIS_IS_BETTER_FOR_EVERYONE | myFlags::ZAP_WITH_LAZER | myFlags::ESCORT_OUT_IMMEDIATE);

    return 0;
}
