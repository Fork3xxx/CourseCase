package com.example.dynamicfragmentdemo;

import android.annotation.SuppressLint;
import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class Fragment_Container extends Fragment {
    private int fragment_index;//表示用哪个Fragment，通过构造方法去确定
    public Fragment_Container(){};
    @SuppressLint("ValidFragment")
    public Fragment_Container(int fragment_index){
        this.fragment_index = fragment_index;

    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_layout,null);
        TextView textView = view.findViewById(R.id.tv_content);
        //根据不同的fragment_index，设置不同的背景颜色和文字信息
        if (fragment_index == 1){
            view.setBackgroundResource(android.R.color.darker_gray);

            textView.setText("This is the first fragment.");

        }
        else if (fragment_index == 2){
            view.setBackgroundResource(android.R.color.background_dark);
            textView.setText("This is the second fragment.");

        }
        else if (fragment_index == 3){
            view.setBackgroundResource(android.R.color.holo_blue_bright);
            textView.setText("This is the third fragment.");

        }
        return view;
    }
}
