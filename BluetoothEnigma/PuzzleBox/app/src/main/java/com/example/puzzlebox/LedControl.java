package com.example.puzzlebox;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

public class LedControl extends AppCompatActivity {

    public static final int MORSE_CODE_REQUEST_CODE = 1;
    private Button btnDisconnect;

    private Button morseCodeFolder, morseCodeLetters, morseCodeNumbers, morseCodeSpecial;
    private LinearLayout morseCodeLayout;

    private Button coreFolder;
    private boolean isCoreFolderUnlocked = false;
    private Button openHatch;
    private boolean isHatchOpen = false;

    private Button adminFolder;
    private boolean isAdminFolderUnlocked = false;
    private Button interruptProgram;

    private String address = null;
    private BluetoothAdapter bluetoothAdapter = null;
    private BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    private ProgressDialog progress;

    private static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_led_control);

        Intent intent = getIntent();
        address = intent.getStringExtra(MainActivity.EXTRA_ADDRESS);

        morseCodeFolder = findViewById(R.id.morseCodeFolder);
        morseCodeLetters = findViewById(R.id.morseCodeLetters);
        morseCodeNumbers = findViewById(R.id.morseCodeNumbers);
        morseCodeSpecial = findViewById(R.id.morseCodeSpecial);
        morseCodeLayout = findViewById(R.id.morseCodeLayout);

        coreFolder = findViewById(R.id.coreFolder);
        openHatch = findViewById(R.id.openHatch);

        adminFolder = findViewById(R.id.adminFolder);
        interruptProgram = findViewById(R.id.interruptProgram);

        btnDisconnect = findViewById(R.id.btnDisconnect);

        new LedControl.ConnectBT().execute();
        //start morse code

        morseCodeFolder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendSignal("2");
                handleMorseCodeFolder();
            }
        });

        morseCodeLetters.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                displayLetters();
            }
        });

        morseCodeNumbers.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                displayNumbers();
            }
        });

        morseCodeSpecial.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                displaySpecial();
            }
        });

        coreFolder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isCoreFolderUnlocked) {
                    openEnterMorseCode();
                } else {
                    openCoreFolder();
                }
                
            }
        });

        openHatch.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
            @Override
            public void onClick(View v) {
                sendSignal("3");
                isHatchOpen = true;
                grantAdminAccess();
            }
        });

        adminFolder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isAdminFolderUnlocked) {
                    Toast.makeText(LedControl.this, "Résous d'abord l'énigme", Toast.LENGTH_LONG).show();
                } else {
                    openAdminFolder();
                }
            }
        });

        interruptProgram.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(LedControl.this, "Bravo! Tu as vaincu Ultron", Toast.LENGTH_LONG).show();
            }
        });

        btnDisconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Disconnect();
            }
        });
    }

    private void openAdminFolder() {
        if (interruptProgram.getVisibility() == View.GONE) {
            interruptProgram.setVisibility(View.VISIBLE);
        } else {
            interruptProgram.setVisibility(View.GONE);
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    private void grantAdminAccess() {
        adminFolder.setBackgroundTintList(getResources().getColorStateList(R.color.purple_500));
        adminFolder.setTextColor(getApplication().getResources().getColor(R.color.white));
        adminFolder.setCompoundDrawablesWithIntrinsicBounds(R.drawable.ic_baseline_folder_24, 0, 0, 0);
        isAdminFolderUnlocked = true;
    }

    private void openCoreFolder() {
        if (openHatch.getVisibility() == View.GONE) {
            openHatch.setVisibility(View.VISIBLE);
        } else {
            openHatch.setVisibility(View.GONE);
        }
    }

    private void openEnterMorseCode() {
        Intent i = new Intent(LedControl.this, EnterMorseCode.class);
        startActivityForResult(i, MORSE_CODE_REQUEST_CODE);
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == MORSE_CODE_REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                //le code morse est bon on débloque le bouton access to core elements
                coreFolder.setBackgroundTintList(getResources().getColorStateList(R.color.purple_500));
                coreFolder.setTextColor(getApplication().getResources().getColor(R.color.white));
                coreFolder.setCompoundDrawablesWithIntrinsicBounds(R.drawable.ic_baseline_folder_24, 0, 0, 0);
                isCoreFolderUnlocked = true;
            }
        }
    }

    private void displaySpecial() {
        Intent i = new Intent(LedControl.this, DisplayMorseCode.class);
        i.putExtra("imageView", "special");
        startActivity(i);
    }

    private void displayNumbers() {
        Intent i = new Intent(LedControl.this, DisplayMorseCode.class);
        i.putExtra("imageView", "numbers");
        startActivity(i);
    }

    private void displayLetters() {
        Intent i = new Intent(LedControl.this, DisplayMorseCode.class);
        i.putExtra("imageView", "letters");
        startActivity(i);
    }

    private void handleMorseCodeFolder() {
        if (morseCodeLayout.getVisibility() == View.GONE) {
            morseCodeLayout.setVisibility(View.VISIBLE);
        } else {
            morseCodeLayout.setVisibility(View.GONE);
        }
    }

    private void sendSignal ( String number ) {
        if (btSocket != null) {
            try {
                btSocket.getOutputStream().write(number.toString().getBytes());
                Log.e("SendSignal", number);
            } catch (IOException e) {
                Log.e("SendSignal", e.getMessage());
            }
        }
    }

    private void Disconnect () {
        if (btSocket!=null) {
            try {
                btSocket.close();
            } catch(IOException e) {
                Log.e("Disconnect", e.getMessage());
            }
        }

        finish();
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void> {
        private boolean ConnectSuccess = true;

        @Override
        protected  void onPreExecute () {
            progress = ProgressDialog.show(LedControl.this, "Connecting...", "Please Wait!!!");
        }

        @Override
        protected Void doInBackground (Void... devices) {
            try {
                if ( btSocket==null || !isBtConnected ) {
                    bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice dispositivo = bluetoothAdapter.getRemoteDevice(address);
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();
                }
            } catch (IOException e) {
                ConnectSuccess = false;
            }

            return null;
        }

        @Override
        protected void onPostExecute (Void result) {
            super.onPostExecute(result);

            if (!ConnectSuccess) {
                Log.e("ConnectBT", "Connection Failed");
                finish();
            } else {
                Log.e("ConnectBT", "Connected");
                isBtConnected = true;
            }

            progress.dismiss();
        }
    }
}