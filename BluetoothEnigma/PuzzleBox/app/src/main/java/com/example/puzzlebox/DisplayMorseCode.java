package com.example.puzzlebox;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageView;

public class DisplayMorseCode extends AppCompatActivity {

    private ImageView imageView;
    private String chooseImage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_morse_code);

        imageView = findViewById(R.id.imageView);

        Intent i = getIntent();
        chooseImage = i.getStringExtra("imageView");
        if (chooseImage.equals("letters")) {
            imageView.setImageDrawable(getResources().getDrawable(R.drawable.morse_code_letters));
        } else if (chooseImage.equals("numbers")) {
            imageView.setImageDrawable(getResources().getDrawable(R.drawable.morse_code_numbers));
        } else if (chooseImage.equals("special")) {
            imageView.setImageDrawable(getResources().getDrawable(R.drawable.morse_code_special));
        }

    }
}