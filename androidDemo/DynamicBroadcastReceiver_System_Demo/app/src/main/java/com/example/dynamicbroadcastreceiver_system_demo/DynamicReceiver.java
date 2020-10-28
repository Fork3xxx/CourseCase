package com.example.dynamicbroadcastreceiver_system_demo;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class DynamicReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        //通过intent获取电量
        int level = intent.getIntExtra("level",0);
        Toast.makeText(context,"当前电量是： "+ level + "%",Toast.LENGTH_SHORT).show();
    }
}
