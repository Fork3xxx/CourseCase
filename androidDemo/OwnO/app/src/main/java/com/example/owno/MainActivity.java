package com.example.owno;



import android.os.Bundle;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;


import java.util.ArrayList;
import java.util.List;



public class MainActivity extends AppCompatActivity {




	//要切换显示的四个Fragment
	private HomeFragment homeFragment;
	private DynamicFragment dynamicFragment;
	private MessageFragment messageFragment;

	private UserCenterFragment userCenterFragment;

	private int currentId = R.id.tv_main;// 当前选中id,默认是主页

	private TextView tvMain, tvDynamic, tvMessage, tvPerson;//底部四个TextView

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);







		//底部导航栏

		tvMain = (TextView) findViewById(R.id.tv_main);
		tvMain.setSelected(true);//首页默认选中
		tvDynamic = (TextView) findViewById(R.id.tv_dynamic);
		tvMessage = (TextView) findViewById(R.id.tv_message);
		tvPerson = (TextView ) findViewById(R.id.tv_person);

		//默认加载首页
		homeFragment = new HomeFragment();
		getSupportFragmentManager().beginTransaction().add(R.id.main_container,homeFragment).commit();

		tvMain.setOnClickListener(tabClickListener);
		tvDynamic.setOnClickListener(tabClickListener);
		tvMessage.setOnClickListener(tabClickListener);
		tvPerson.setOnClickListener(tabClickListener);
		findViewById(R.id.iv_make).setOnClickListener(onClickListener);
	}
	
	private OnClickListener onClickListener=new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.iv_make:
				Toast.makeText(MainActivity.this,"点击了制作按钮",Toast.LENGTH_SHORT).show();
				break;
			}
		}
	};

	private OnClickListener tabClickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			if (v.getId() != currentId) {//如果当前选中跟上次选中的一样,不需要处理
				changeSelect(v.getId());//改变图标跟文字颜色的选中 
				changeFragment(v.getId());//fragment的切换
				currentId = v.getId();//设置选中id
			}
		}
	};




	/**
	 * 改变fragment的显示
	 * @param resId
	 */
	private void changeFragment(int resId) {
		FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();//开启一个Fragment事务
		
		hideFragments(transaction);//隐藏所有fragment
		if(resId==R.id.tv_main){//主页
			if(homeFragment==null){//如果为空先添加进来.不为空直接显示
				homeFragment = new HomeFragment();
				transaction.add(R.id.main_container,homeFragment);
			}else {
				transaction.show(homeFragment);//显示首页的Fragment
			}
		}else if(resId==R.id.tv_dynamic){//动态
			if(dynamicFragment==null){
				dynamicFragment = new DynamicFragment();
				transaction.add(R.id.main_container,dynamicFragment);
			}else {
				transaction.show(dynamicFragment);
			}
		}else if(resId==R.id.tv_message){//消息中心
			if(messageFragment==null){
				messageFragment = new MessageFragment();
				transaction.add(R.id.main_container,messageFragment);
			}else {
				transaction.show(messageFragment);
			}
		}else if(resId==R.id.tv_person){//我
			if(userCenterFragment== null){
				userCenterFragment=new UserCenterFragment();
				transaction.add(R.id.main_container,userCenterFragment);
			}else {
				transaction.show(userCenterFragment);
			}
		}
		transaction.commit();//一定要记得提交事务
	}
	
	/**
	 * 显示之前隐藏所有fragment
	 * @param transaction
	 */
	private void hideFragments(FragmentTransaction transaction){
		if (homeFragment != null)//不为空才隐藏,如果不判断第一次会有空指针异常
			transaction.hide(homeFragment);
		if (dynamicFragment != null)
			transaction.hide(dynamicFragment);
		if (messageFragment != null)
			transaction.hide(messageFragment);
		if (userCenterFragment != null)
			transaction.hide(userCenterFragment);
	}

	/**
	 * 改变TextView选中颜色
	 * @param resId
	 */
	private void changeSelect(int resId){
		tvMain.setSelected(false);
		tvDynamic.setSelected(false);
		tvMessage.setSelected(false);
		tvPerson.setSelected(false);

		switch (resId) {
		case R.id.tv_main:
			tvMain.setSelected(true);
			break;
		case R.id.tv_dynamic:
			tvDynamic.setSelected(true);
			break;
		case R.id.tv_message:
			tvMessage.setSelected(true);
			break;
		case R.id.tv_person:
			tvPerson.setSelected(true);
			break;
		}
	}






}

