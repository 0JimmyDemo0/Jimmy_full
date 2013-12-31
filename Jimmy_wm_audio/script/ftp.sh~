#!/bin/bash
cd /var/www/jimmytwitter/uploads
sleep 3
sftp -b sftp_batch interaction@interaction
sleep 0.5
convert -crop 800x600+100+50 photo.jpg photo_trans.jpg
eog photo_trans.jpg &
