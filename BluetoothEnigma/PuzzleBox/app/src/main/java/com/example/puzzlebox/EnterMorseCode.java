package com.example.puzzlebox;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class EnterMorseCode extends AppCompatActivity {

    private Button confirmCode;
    private EditText enterCode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_enter_morse_code);

        enterCode = findViewById(R.id.enterMorseCode);
        confirmCode = findViewById(R.id.confirmCode);

        confirmCode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                checkCode();
            }
        });
    }

    private void checkCode() {
        String enteredCode = enterCode.getText().toString().trim();

        if (enteredCode.equals("IEE 802.15")) {
            Toast.makeText(EnterMorseCode.this, "Code bon", Toast.LENGTH_LONG).show();
            Intent i = new Intent(EnterMorseCode.this, LedControl.class);
            setResult(RESULT_OK, i);
            finish();
        } else {
            Toast.makeText(EnterMorseCode.this, "Essaye encore", Toast.LENGTH_LONG).show();
            Intent i = new Intent(EnterMorseCode.this, LedControl.class);
            setResult(RESULT_CANCELED, i);
            finish();
        }
    }
}