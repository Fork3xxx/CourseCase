package com.example.dynamicbroadcastreceiver_system_demo;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class StaticBroadcastReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        String data = intent.getStringExtra("data");
        Toast.makeText(context,"广播已接收，数据为："+ data,Toast.LENGTH_SHORT).show();
    }
}
