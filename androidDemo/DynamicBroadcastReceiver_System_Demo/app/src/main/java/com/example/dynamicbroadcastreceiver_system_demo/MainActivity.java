package com.example.dynamicbroadcastreceiver_system_demo;

import android.content.Intent;
import android.content.IntentFilter;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    private DynamicReceiver dynamicReceiver;
    private EditText et_data;
    private Button btn_sendbroadcast;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        et_data = findViewById(R.id.et_data);
        btn_sendbroadcast = findViewById(R.id.btn_sendbroadcast);
        btn_sendbroadcast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                //发送多个：putExtras，把自己的数据打个包，buddle,或者，复制多次putExtra
                intent.putExtra("data",et_data.getText().toString());  //携带数据
                intent.setAction("mybroadcast");  //设定广播的名称或者频道
                sendBroadcast(intent);              //发送广播
            }
        });

        //动态注册广播
        dynamicReceiver = new DynamicReceiver();
        IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);//给出广播名
          registerReceiver(dynamicReceiver,filter);

    }
    //当不用广播时，最好注销广播，这样可以减少资源消耗
    @Override
    protected  void onDestroy() {
        //注销广播
        unregisterReceiver(dynamicReceiver);
        super.onDestroy();
    }

}

