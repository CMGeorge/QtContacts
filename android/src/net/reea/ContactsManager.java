package net.reea;

import android.provider.ContactsContract;
import android.content.Context;
import android.database.Cursor;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

public class ContactsManager extends org.qtproject.qt5.android.bindings.QtActivity{
     public ContactsManager(){
     }

    public static String getContacts(Context c) {
//        ActivityCompat.requestPermissions(this,new String[]{Manifest.permission.READ_CONTACTS},1);
//        String fetch="<root>";
        Cursor phones = c.getContentResolver().query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null, null, null, null);

        JSONArray jsonArray = new JSONArray();
        while (phones.moveToNext()) {
            JSONObject contactDetail = new JSONObject();

            try {
                contactDetail.put("name", phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME)));
                contactDetail.put("photo", phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.PHOTO_THUMBNAIL_URI )));
                contactDetail.put("phoneNumber", phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER)));

            } catch (JSONException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }


//            String name = phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME));
//            String phoneNumber = phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
//            fetch+="<item><name>"+name+"</name><number>"+phoneNumber+"</number></item>";

            jsonArray.put(contactDetail);
        }
//        fetch+="</root>";
        String jsonStr = jsonArray.toString();
        System.out.println("jsonString: "+jsonStr);
        return jsonStr;
    }
}
