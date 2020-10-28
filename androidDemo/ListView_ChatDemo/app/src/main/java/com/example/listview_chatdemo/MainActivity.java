package com.example.listview_chatdemo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {


    private ListView listView;
    private ArrayList<Message> data;
    private MyAdapter myAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listView = findViewById(R.id.lv_chat);
        initData();
        myAdapter = new MyAdapter(data,this);
        listView.setAdapter(myAdapter);
    }

    private void initData() {
        String[] content = {"你好", "你好","这里是食杳","好的","为什么扩列呢"," 超喜欢"," 《Blood Blockade Battlefront》、《91days》","《Baccano！》"," 《DRRR!》","我们的目标是文画双修！！","擅长躺列，空间点赞，大佬舔狗","看我"};
       // int[] head = {R.mipmap.person1, R.mipmap.person2};
        boolean[] isSend={true,false,true,false,false,true,true,true,true,true,true,true};
        data = new ArrayList<Message>();
        for (int i = 0; i < content.length; i++) {
            Message message = new Message(content[i], isSend[i]);
            data.add(message);
        }
    }
}


