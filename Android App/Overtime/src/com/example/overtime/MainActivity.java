package com.example.overtime;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import android.app.Activity;
import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.TimePicker;
 
public class MainActivity extends Activity {
 
	private TextView tvDisplayTime;
	private Button btnChangeTime;
 
	private TextView endTvTime;
	private Button endBtn;
	
	private TextView overtimeTvTime;
	
	private int shour = 0;
	private int sminute = 0;
	
	private int ehour = 0;
	private int eminute = 0;
	
	static final int TIME_DIALOG_ID = 999;
	static final int TIME_DIALOG_ID_END = 998;
 
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
 
		setCurrentTimeOnView();
		addListenerOnButton();
	}
 
	// display current time
	public void setCurrentTimeOnView() {
 
		tvDisplayTime = (TextView) findViewById(R.id.tvTime);
		endTvTime = (TextView) findViewById(R.id.endTvTime);
 
		final Calendar c = Calendar.getInstance();
		shour = c.get(Calendar.HOUR_OF_DAY);
		sminute = c.get(Calendar.MINUTE);
		
		ehour = c.get(Calendar.HOUR_OF_DAY);
		eminute = c.get(Calendar.MINUTE);
		
		// set current time into textview
		tvDisplayTime.setText(
                    new StringBuilder().append(pad(shour))
                                       .append(":").append(pad(sminute)));
		endTvTime.setText(
                new StringBuilder().append(pad(ehour))
                                   .append(":").append(pad(eminute)));
 
	}
 
	public void addListenerOnButton() {
 
		btnChangeTime = (Button) findViewById(R.id.btnChangeTime);
		endBtn = (Button) findViewById(R.id.btnChangeTimeEnd);
		
		btnChangeTime.setOnClickListener(new OnClickListener() {
 
			@Override
			public void onClick(View v) {
				showDialog(TIME_DIALOG_ID);
			}
 
		});
		 
		endBtn.setOnClickListener(new OnClickListener() {
 
			@Override
			public void onClick(View v) {
				showDialog(TIME_DIALOG_ID_END);
			}
			
		});
		
	}
 
	@Override
	protected Dialog onCreateDialog(int id) {
		switch (id) {
		case TIME_DIALOG_ID:
			// set time picker as current time
			return new TimePickerDialog(this, 
                                        timePickerListener, shour, sminute, true);
 
		case TIME_DIALOG_ID_END:
			// set time picker as current time
			return new TimePickerDialog(this, 
                                        timePickerListenerEnd, ehour, eminute, true);
			
		}
		return null;
	}
 
	private TimePickerDialog.OnTimeSetListener timePickerListener = 
            new TimePickerDialog.OnTimeSetListener() {
		public void onTimeSet(TimePicker view, int selectedHour,
				int selectedMinute) {
			shour = selectedHour;
			sminute = selectedMinute;
 
			// set current time into textview
			tvDisplayTime.setText(new StringBuilder().append(pad(shour))
					.append(":").append(pad(sminute)));
 
		}
	};
 
	private TimePickerDialog.OnTimeSetListener timePickerListenerEnd = 
            new TimePickerDialog.OnTimeSetListener() {
				
		public void onTimeSet(TimePicker view, int selectedHour,
				int selectedMinute) {
			ehour = selectedHour;
			eminute = selectedMinute;
 
			// set current time into textview
			endTvTime.setText(new StringBuilder().append(pad(ehour))
					.append(":").append(pad(eminute)));

			try {
				calculateOT();
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	};
	
	private static String pad(int c) {
		if (c >= 10)
		   return String.valueOf(c);
		else
		   return "0" + String.valueOf(c);
	}
	
	private void calculateOT() throws ParseException {
		overtimeTvTime = (TextView) findViewById(R.id.overtimeTv);
		
		// count hours
		int temph = shour;
		int i = 0;
		for(i = 0; temph % 24 != ehour; i++){
			temph %= 24;
			temph++;
		}
		
		// determine minutes
		int tempm = 0;
		
		// if starting minutes is less than ending minutes
		if(eminute <= sminute){
			// calculate the minutes it takes from the ending minutes to get
			// to the full hour and add that to the starting minutes
			tempm = sminute + (60 - eminute);
			
			// if there are more than 60 minutes
			if(tempm > 60)
			{
				// subtract the amount of hours from that 60 minutes from
				// the hours counted by i
				i -= (tempm / 60);
				
				// if there are no hours counted by i
				// set i to 23
				if(i < 0)
					i = 23;
				
				// the remaining minutes
				tempm = 60 - (tempm % 60);
			}
			else 
			// if there are less than 60 minutes
			// the remainder is the minutes
				tempm %= 60;
		}
		else{
		// ending minutes greater than starting minutes
			tempm = eminute - sminute;
		}
		
/*****************       ************************/		
		
		// the amount of minutes on a regular shift
		int regularTime = (8 * 60 + 35);
		
		// regular shift = no overtime
		if(regularTime >= (i * 60) + tempm){
			overtimeTvTime.setText("00:00");
		}
		else
		{
			// if less than an hour of overtime
			if(tempm >= 35)
			{
				overtimeTvTime.setText(String.valueOf(pad(i - 8))+":"+String.valueOf(pad(tempm - 35)));
			}
			// if there is over an hour of overtime
			else{
				int otminutes = 60 + (tempm - 35);
				int otHours = i - 9;
				overtimeTvTime.setText(String.valueOf(pad(otHours))+":"+String.valueOf(pad(otminutes)));
			}
		}
			
	}
}

