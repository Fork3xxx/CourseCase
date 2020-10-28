package com.example.owno;



import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;


public class DynamicFragment extends Fragment {
	private List<String> data;
	private LayoutInflater inflater;
	private List<String> items;




	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {


		View rootView = inflater.inflate(R.layout.fragment_dynamic, null);
		initDynamicData();
		return rootView;


	}

	//初始化动态数据
	private void initDynamicData(){
		items = new ArrayList<>();
		for(int i=0;i<5;i++){
			items.add("item;"+(i+1));
		}
	}
}
