package com.example.listview_customiszedadapterdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {


    private ListView listView;
    private ArrayList<Person> data;
    private MyAdapter myAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listView = findViewById(R.id.lv_person);
        initData();
        myAdapter = new MyAdapter(data,this);
        listView.setAdapter(myAdapter);
    }

    private void initData() {
        String[] name = {"小蓝", "小红", "小绿"};
        int[] head = {R.mipmap.person1, R.mipmap.person2, R.mipmap.person3};
        data = new ArrayList<Person>();
        for (int i = 0; i < name.length; i++) {
            Person person = new Person(name[i], head[i]);
            data.add(person);
        }
    }
}


