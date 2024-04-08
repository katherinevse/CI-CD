#!/bin/bash

API_TOKEN="7149887935:AAEDHytI1aa-N_b_A0suyJslIOj9sBA1roI"
CHAT_ID="5075602717"
URL="https://api.telegram.org/bot$API_TOKEN/sendMessage"
TEXT="FROM:+$CI_COMMIT_AUTHOR%0A%0AJOB: $CI_JOB_NAME%0A%0ASTATUS:+$CI_JOB_STATUS%0A%0APROJECT:+$CI_PROJECT_NAME"

curl -s -d "chat_id=$CHAT_ID&disable_web_page_preview=1&text=$TEXT" $URL 
