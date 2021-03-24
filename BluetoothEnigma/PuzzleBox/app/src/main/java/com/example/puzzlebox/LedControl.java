package com.example.puzzlebox;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.util.UUID;

public class LedControl extends AppCompatActivity {

    private Button btn0, btn1, btnDisconnect;

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

        btn0 = findViewById(R.id.btn0);
        btn1 = findViewById(R.id.btn1);
        btnDisconnect = findViewById(R.id.btnDisconnect);

        new LedControl.ConnectBT().execute();

        btn0.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendSignal("0");
            }
        });

        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendSignal("1");
            }
        });

        btnDisconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Disconnect();
            }
        });
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