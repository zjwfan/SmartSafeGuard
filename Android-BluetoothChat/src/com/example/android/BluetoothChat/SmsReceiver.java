/**
 * 
 */
package com.example.android.BluetoothChat;

//import org.crazyit.ui.ToastTest;

//import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
//import android.graphics.Color;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.view.Gravity;
//import android.view.LayoutInflater;
//import android.view.View;
//import android.view.ViewGroup;
//import android.widget.ImageView;
//import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;



/**
 * Description:
 * <br/>网站: <a href="http://www.crazyit.org">疯狂Java联盟</a> 
 * <br/>Copyright (C), 2001-2012, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class SmsReceiver extends BroadcastReceiver
{	
	
	// 当接收到短信时被触发
	@Override
	public void onReceive(Context context, Intent intent)
	{
		
		// 如果是接收到短信
		if (intent.getAction().equals(
			"android.provider.Telephony.SMS_RECEIVED"))
		{
			
			
			
			// 取消广播（这行代码将会让系统收不到短信）
			//abortBroadcast();
			//让系统也接收短信 	便于保存
			
			
			
			
			
			StringBuilder sb = new StringBuilder();
			// 接收由SMS传过来的数据
			Bundle bundle = intent.getExtras();
			// 判断是否有数据
			if (bundle != null)
			{
				//  通过pdus可以获得接收到的所有短信消息
				Object[] pdus = (Object[]) bundle.get("pdus");
				// 构建短信对象array,并依据收到的对象长度来创建array的大小 
				SmsMessage[] messages = new SmsMessage[pdus.length];
				
				
				for (int i = 0; i < pdus.length; i++)
				{
					messages[i] = SmsMessage
						.createFromPdu((byte[]) pdus[i]);
				}
				
				// 将送来的短信合并自定义信息于StringBuilder当中 
				/*
				for (SmsMessage message : messages)
				{
					//sb.append("短信来源:");
					// 获得接收短信的电话号码
					//sb.append(message.getDisplayOriginatingAddress());
					sb.append("智能安全卫士提示\n");
					
					//sb.append("\n------短信内容------\n");
					// 获得短信的内容
					sb.append(message.getDisplayMessageBody());
				}
				*/
				//由于短信的Toast弹窗效果不好 隐去
			}
			
			//Toast toast = Toast.makeText(context,sb.toString(), 5000);
			
			
			
			//标题栏的添加 失败
			/*
				LayoutInflater inflater = (LayoutInflater) ((Activity) context).getLayoutInflater();
			   View layout = inflater.inflate(R.layout.picture,
			     (ViewGroup) ((Activity) context).findViewById(R.id.picture));
			   ImageView image = (ImageView) layout
			     .findViewById(R.id.cold_play);
			   image.setImageResource(R.drawable.cold_play);
			   TextView title = (TextView) layout.findViewById(R.id.tvTitleToast);
			   title.setText("Attention");
			   TextView text = (TextView) layout.findViewById(R.id.tvTextToast);
			   text.setText("完全自定义Toast");
			   Toast toast = new Toast(context.getApplicationContext());
			   toast.setGravity(Gravity.RIGHT | Gravity.TOP, 12, 40);
			   toast.setDuration(Toast.LENGTH_LONG);
			   toast.setView(layout);
			   toast.show();
			
			*/
			//标题栏的添加 失败
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			//大小
			TextView textView = new TextView(context);
			
			
			
			textView.setText(sb.toString());
			// 设置文本框内字体的大小和颜色
			textView.setTextSize(40);
			//textView.setTextColor(Color.MAGENTA);	//紫色
			
			//5000持续时间更改
			Toast toast = Toast.makeText(context,sb.toString(), 20000);
			toast.setView(textView);
			
			
			
			
			toast.setGravity(Gravity.CENTER, 0, 0);
			toast.show();
			//大小
			
			
			
			
			
			
			
			
			
			
			/*
			Toast toast=new Toast(this);

	           toast.setView(view);

	           //载入view,即显示toast.xml的内容

	           TextView tv=(TextView)view.findViewById(R.id.tv1);

	           tv.setText("Toast显示View内容");

	           //修改TextView里的内容

	           toast.setDuration(Toast.LENGTH_SHORT);

	           //设置显示时间，长时间Toast.LENGTH_LONG，短时间为Toast.LENGTH_SHORT,不可以自己编辑

	           toast.show();

			 	*/
			
			
			
			
			/*
			 Intent activityIntent = new Intent();
			 intent.setClass(Context packageContext, ToastTest) ; 
			 
	        Intent activityIntent = new Intent(context, ToastTest.class);    
	        //  要想在Service中启动Activity，必须设置如下标志（网上搜的才知道这点）    
	        activityIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);    
	        context.startActivity(activityIntent);  
			*/
			
			//ToastTest.toast.show();

			
		}	
	}
	
	/*
	public static class ToastTest extends Activity
	{
		public static Toast toast;

		//@Override
		public void onCreate(Bundle savedInstanceState)
		{
			super.onCreate(savedInstanceState);
			setContentView(R.layout.main);
		
		
			
				
					// 创建一个Toast提示信息
					toast = new Toast(ToastTest.this);
					// 设置Toast的显示位置
					toast.setGravity(Gravity.CENTER, 0, 0);
					// 创建一个ImageView
					ImageView image = new ImageView(ToastTest.this);
					image.setImageResource(R.drawable.app_icon);
					// 创建一个LinearLayout容器
					LinearLayout ll = new LinearLayout(ToastTest.this);
					// 向LinearLayout中添加图片、原有的View
					ll.addView(image);
					// 创建一个ImageView
					TextView textView = new TextView(ToastTest.this);
					textView.setText("带图片的提示信");
					// 设置文本框内字体的大小和颜色
					textView.setTextSize(30);
					textView.setTextColor(Color.MAGENTA);
					ll.addView(textView);
					 //设置Toast显示自定义View				
					toast.setView(ll);
					// 设置Toast的显示时间
					toast.setDuration(Toast.LENGTH_LONG);
					//toast.show();
				
					
		}
	}
	*/
}
