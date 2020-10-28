package com.example.owno;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

import java.util.ArrayList;


public class MessageFragment extends Fragment {


	private ListView listView;
	private ArrayList<Message> data;
	private MessageAdapter myAdapter;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_message, null);

		initData();

		return rootView;


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
