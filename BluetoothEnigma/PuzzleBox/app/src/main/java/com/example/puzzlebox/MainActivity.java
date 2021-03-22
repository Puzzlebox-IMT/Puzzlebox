package com.example.puzzlebox;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Set;

public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_CODE_ENABLE_BLUETOOTH = 1 ;

    private TextView bluetoothStatus;
    private Button displayPairedDevices;

    private BluetoothAdapter bluetoothAdapter = null;
    private Set<BluetoothDevice> pairedDevices;
    private ListView deviceList;

    public static String EXTRA_ADDRESS = "device_address";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        //INIT
        if (bluetoothAdapter == null) {
            //device does not have bluetooth
            setContentView(R.layout.no_bluetooth);
            //close app
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    MainActivity.this.finish();
                }
            }, 30000);
        } else {
            //device has bluetooth
            setContentView(R.layout.activity_main);

            bluetoothStatus = findViewById(R.id.bluetoothStatus);

            displayPairedDevices = findViewById(R.id.displayPairedDevices);
            displayPairedDevices.setEnabled(false);
            displayPairedDevices.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (bluetoothAdapter.isEnabled()) {
                        pairedDevicesList();
                    } else {
                        Toast.makeText(MainActivity.this, "Veuillez activer le bluetooth pour continuer", Toast.LENGTH_SHORT).show();
                    }

                }
            });

            deviceList = findViewById(R.id.deviceList);

            if (!bluetoothAdapter.isEnabled()) {
                bluetoothStatus.setText("Le bluetooth n'est pas activé");
                Intent enableBluetoothIntent= new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBluetoothIntent, REQUEST_CODE_ENABLE_BLUETOOTH);
            }

        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode!= REQUEST_CODE_ENABLE_BLUETOOTH) {
            return;
        } else {
            if (resultCode == RESULT_OK) {
                //l'utilisateur a activé le bluetooth
                bluetoothStatus.setText("Le bluetooth est activé");
                displayPairedDevices.setEnabled(true);
            } else {
                //pas d'activation du bluetooth
                Toast.makeText(MainActivity.this, "Veuillez activer le bluetooth pour continuer", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void pairedDevicesList () {
        pairedDevices = bluetoothAdapter.getBondedDevices();
        ArrayList list = new ArrayList();

        if (pairedDevices.size() > 0) {
            for (BluetoothDevice bt : pairedDevices) {
                list.add(bt.getName().toString() + "\n" + bt.getAddress().toString());
            }
        } else {
            Toast.makeText(getApplicationContext(), "No Paired Bluetooth Devices Found.", Toast.LENGTH_LONG).show();
        }

        final ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, list);
        deviceList.setAdapter(adapter);
        deviceList.setOnItemClickListener(myListClickListener);
    }

    private AdapterView.OnItemClickListener myListClickListener = new AdapterView.OnItemClickListener() {
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            String info = ((TextView) view).getText().toString();
            String address = info.substring(info.length()-17);

            Intent i = new Intent(MainActivity.this, LedControl.class);
            i.putExtra(EXTRA_ADDRESS, address);
            startActivity(i);
        }
    };
}