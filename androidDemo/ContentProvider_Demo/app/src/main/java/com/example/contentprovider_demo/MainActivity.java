package com.example.contentprovider_demo;

import android.database.Cursor;
import android.provider.ContactsContract;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    private ListView lv_contacts;
    private List<Map<String,String>> data;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //listview控件元素
        lv_contacts = findViewById(R.id.lv_contacts);

        //数据
        Cursor cursor = getContentResolver().query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                null,null,null,null);
        while (cursor.moveToNext()){
            String name = cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME));
            String phone = cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
            //构造联系人
            Map<String,String> map = new HashMap<String, String>();
            map.put("name",name);
            map.put("phone",phone);
            data.add(map);  //将联系人添加到data中
        }

        //适配器元素
        SimpleAdapter adapter = new SimpleAdapter(this,data,android.R.layout.simple_list_item_2,
                new String[]{"name","phone"},new int[]{android.R.id.text1,android.R.id.text2});

        //设置适配器
        lv_contacts.setAdapter(adapter);

    }
}
