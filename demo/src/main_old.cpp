#include "account.hpp"
#include "app.hpp"
#include "detail/oauth.hpp"
#include "message.hpp"
#include "objects/user.hpp"
#include "objects/tweet.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

int main() {
    tal::App daytime{"flxndnoaoOxzseVrt1dx61iZx",
                     "HdSCNMhaWQAWUswvEymQqC11p0nVSpf1qvZykUYe5jdgYYchHU"};
    tal::Account bot_account{
        "838185577975533571-2PXBkay7faR0b3lT7f3K2fKX2t7CAe3",
        "UC3HtOyZuGSFHZR7JD2tSKMHRoaSVZ8AWPQONEjXku5Rn"};

    daytime.set_account(bot_account);

    auto handler = [](const tal::Message& m) {
        std::cout << tal::Tweet(m).text << '\n' << std::endl;
    };

    daytime.filtered_stream().add_track("water");
    daytime.register_to_filtered_stream(handler);

    // tal::User u{R"()"};

    // std::cout << u << std::endl;

//     tal::Tweet twt{
//         R"foo({"created_at":"Mon Apr 10 22:25:44 +0000 2017","id":851561866031706112,"id_str":"851561866031706112","text":"\u201cMost obvious impacts are in those parks with glaciers\" and in tropics (islands): melting + parking lots under water #NationalParks","source":"\u003ca href=\"http:\/\/twitter.com\" rel=\"nofollow\"\u003eTwitter Web Client\u003c\/a\u003e","truncated":false,"in_reply_to_status_id":null,"in_reply_to_status_id_str":null,"in_reply_to_user_id":null,"in_reply_to_user_id_str":null,"in_reply_to_screen_name":null,"user":{"id":430148484,"id_str":"430148484","name":"Eric Gershon","screen_name":"Gershonicus","location":"Boulder","url":"http:\/\/www.colorado.edu\/coloradan\/","description":"Editor, Coloradan mag @CUBoulder Past: staff writer @HartfordCourant, city hall correspondent @sfexaminer. \"And here I am in Colorado!\" \u2014 Kerouac, OTR","protected":false,"verified":false,"followers_count":510,"friends_count":813,"listed_count":22,"favourites_count":525,"statuses_count":1438,"created_at":"Tue Dec 06 20:34:08 +0000 2011","utc_offset":-14400,"time_zone":"Eastern Time (US & Canada)","geo_enabled":false,"lang":"en","contributors_enabled":false,"is_translator":false,"profile_background_color":"C0DEED","profile_background_image_url":"http:\/\/abs.twimg.com\/images\/themes\/theme1\/bg.png","profile_background_image_url_https":"https:\/\/abs.twimg.com\/images\/themes\/theme1\/bg.png","profile_background_tile":false,"profile_link_color":"1DA1F2","profile_sidebar_border_color":"C0DEED","profile_sidebar_fill_color":"DDEEF6","profile_text_color":"333333","profile_use_background_image":true,"profile_image_url":"http:\/\/pbs.twimg.com\/profile_images\/776903937634897920\/5R3MNu_b_normal.jpg","profile_image_url_https":"https:\/\/pbs.twimg.com\/profile_images\/776903937634897920\/5R3MNu_b_normal.jpg","profile_banner_url":"https:\/\/pbs.twimg.com\/profile_banners\/430148484\/1398888738","default_profile":true,"default_profile_image":false,"following":null,"follow_request_sent":null,"notifications":null},"geo":null,"coordinates":null,"place":null,"contributors":null,"is_quote_status":false,"retweet_count":0,"favorite_count":0,"entities":{"hashtags":[{"text":"NationalParks","indices":[117,131]}],"urls":[],"user_mentions":[],"symbols":[]},"favorited":false,"retweeted":false,"filter_level":"low","lang":"en","timestamp_ms":"1491863144773"}
// )foo"};

    // std::cout << twt << std::endl;

    // while (true) {
    //     std::time_t time = std::time(nullptr);
    //     std::tm tm = *std::localtime(&time);
    //     daytime.update_status(std::asctime(&tm));
    //     std::this_thread::sleep_for(std::chrono::minutes(5));
    // }
    return 0;
}
