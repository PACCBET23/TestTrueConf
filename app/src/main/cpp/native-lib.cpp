#include <jni.h>
#include <string>
#include <algorithm>

class StringManipulator {
public:
    void ReverseString(std::wstring& str) {
        int i = 0;
        int j = str.size() - 1;
        while (i < j) {
            wchar_t temp = str[j];
            str[j] = str[i];
            str[i] = temp;
            i++;
            j--;
        }
    }

    std::wstring JStringToWString(JNIEnv* env, jstring input) {
        const jchar* inputChars = env->GetStringChars(input, nullptr);
        jsize inputLen = env->GetStringLength(input);

        std::wstring result(inputLen, L'\0');
        std::copy(inputChars, inputChars + inputLen, result.begin());
        env->ReleaseStringChars(input, inputChars);
        return result;
    }

    jstring WStringToJString(JNIEnv* env, const std::wstring& input) {
        std::basic_string<jchar> jcharStr(input.begin(), input.end());
        return env->NewString(jcharStr.c_str(), jcharStr.length());
    }

    jstring StringFromJNI(JNIEnv* env, jstring input) {
        std::wstring inputStr = JStringToWString(env, input);
        //или же stl reverse
        //std::reverse(inputStr.begin(), inputStr.end());
        ReverseString(inputStr);
        return WStringToJString(env, inputStr);
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_trueconf_trueconftestex_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */,
        jstring input) {
    StringManipulator manipulator;
    return manipulator.StringFromJNI(env, input);
}