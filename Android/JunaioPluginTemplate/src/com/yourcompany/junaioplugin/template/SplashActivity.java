package com.yourcompany.junaioplugin.template;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;

import com.metaio.junaio.plugin.JunaioPlugin;

public class SplashActivity extends Activity {
	static {
		JunaioPlugin.loadNativeLibs();
	}

	/**
	 * standard tag used for all the debug messages
	 */
	public static final String TAG = "junaioPluginTemplate";

	/**
	 * Display log messages with debug priority
	 * 
	 * @param msg
	 *            Message to display
	 * @see Log#d(String, String)
	 */
	public static void log(String msg) {
		if (msg != null)
			Log.d(TAG, msg);

	}

	/**
	 * Progress dialog
	 */
	private ProgressDialog progressDialog;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);

	}

	@Override
	protected void onResume() {
		super.onResume();
		JunaioStarterTask junaioStarter = new JunaioStarterTask();
		junaioStarter.execute(1);
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onStop() {
		super.onStop();

		if (progressDialog != null) {
			progressDialog.dismiss();
		}
	}

	/**
	 * Launch junaio live view
	 */
	private void launchLiveView() {
		// Set your channel id in /res/values/channelid.xml
		int myChannelId = getResources().getInteger(R.integer.channelid);

		// if you have set a channel ID, then load it directly
		if (myChannelId != -1) {
			startChannel(myChannelId);
		} else {
			showDemo();
		}
	}

	private void showDemo() {
		Animation fadein = new AlphaAnimation(0, 1);
		fadein.setDuration(250);
		fadein.setInterpolator(new DecelerateInterpolator());
		fadein.setFillAfter(true);

		findViewById(R.id.buttonGroup).startAnimation(fadein);

	}

	public void startAREL(View v) {
		int ARELChannelID = 124471; // AREL test
		startChannel(ARELChannelID);
	}

	public void startLb(View v) {
		int LLchannelID = 4796; // Wikipedia EN
		startChannel(LLchannelID);
	}

	public void startChannel(int channelId) {
		Intent intent = new Intent(SplashActivity.this, JunaioARViewTestActivity.class);
		intent.putExtra(getPackageName() + ".CHANNELID", channelId);
		startActivity(intent);
	}

	private class JunaioStarterTask extends AsyncTask<Integer, Integer, Integer> {

		@Override
		protected void onPreExecute() {
			progressDialog = ProgressDialog.show(SplashActivity.this, "junaio", "Starting up...");
		}

		@Override
		protected Integer doInBackground(Integer... params) {

			// Set authentication if a private channel is used
			// JunaioPlugin.setAuthentication("username", "password");

			// Start junaio, this will initialize everything the plugin need
			int result = JunaioPlugin.startJunaio(this, getApplicationContext());

			return result;
		}

		@Override
		protected void onProgressUpdate(Integer... progress) {

		}

		@Override
		protected void onPostExecute(Integer result) {
			if (progressDialog != null) {
				progressDialog.cancel();
				progressDialog = null;
			}

			switch (result) {
			case JunaioPlugin.ERROR_EXSTORAGE:
				SplashActivity.log("External storage is not available, closing...");
				finish();
				break;
			case JunaioPlugin.ERROR_INSTORAGE:
				SplashActivity.log("Internal storage is not available, closing...");
				finish();
				break;
			case JunaioPlugin.CANCELLED:
				SplashActivity.log("Starting junaio cancelled");
				break;
			case JunaioPlugin.SUCCESS:
				launchLiveView();
				break;
			}
		}

	}

}
