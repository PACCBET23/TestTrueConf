package com.trueconf.trueconftestex;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("trueconftestex");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setupUI();
    }

    private void setupUI() {
        EditText inputTxt = findViewById(R.id.InputTxt);
        Button sendButton = findViewById(R.id.SendButton);

        sendButton.setOnClickListener(v -> onSendButtonClicked(inputTxt));
    }

    private void onSendButtonClicked(EditText inputTxt) {
        String input = inputTxt.getText().toString();
        String reversedText = stringFromJNI(input);
        outputTxt(reversedText);
    }

    private void outputTxt(String txt) {
        Toast.makeText(this, txt, Toast.LENGTH_LONG).show();
    }

    public native String stringFromJNI(String input);
}


