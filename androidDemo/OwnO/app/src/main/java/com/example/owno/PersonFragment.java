package com.example.owno;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class PersonFragment extends Fragment {
	private Button btn;





	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {


		View rootView = inflater.inflate(R.layout.fragment_person, null);

		final Button btn_login = (Button) rootView.findViewById(R.id.btn_login);
		Button btn_register = (Button) rootView.findViewById(R.id.btn_register);

		btn_login.setOnClickListener(onClickListener);
		btn_register.setOnClickListener(onClickListener);








		return rootView;
	}

	private View.OnClickListener onClickListener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
				case R.id.btn_login:
					Toast.makeText(getActivity(),"点击了登录",Toast.LENGTH_SHORT).show();
					break;
				case  R.id.btn_register:
					Toast.makeText(getActivity(),"点击了注册",Toast.LENGTH_SHORT).show();
			}
		}
	};

}


