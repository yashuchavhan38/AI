# !/usr/bin/env python3
# -*- coding:utf-8 -*-  
# @author: Shengjia Yan
# 2020-10-15 Thursday
# @email: i@yanshengjia.com
# Copyright @ Shengjia Yan. All Rights Reserved.


import csv
import math
import codecs
import string
import pandas as pd
from collections import Counter

lingspam_train_path = '../data/train/lingspam_train.csv'
lingspam_test_path = '../data/test/lingspam_test.csv'
dtype={
    'email_subject': str,
    'email_body': str,
    'part_name': str,
    'file_name':str,
    'is_spam': int
    }

lingspam_train_df = pd.read_csv(lingspam_train_path, dtype=dtype)
lingspam_test_df = pd.read_csv(lingspam_test_path, dtype=dtype)

print("Dataset column names:")
for col in lingspam_train_df.columns:
  print(col)

print('\nlingspam trainset:')
print(lingspam_train_df)
print('\nlingspam testset:')
print(lingspam_test_df)

trainset_size = lingspam_train_df.shape[0]
testset_size = lingspam_test_df.shape[0]
print("\nTrainset size: " + str(trainset_size))
print("Testset size: " + str(testset_size))


# make dictionary
words = []
dictionary = {}

for index, row in lingspam_train_df.iterrows():
  email = row['email_body'].split(' ')
  email = [word for word in email if word not in string.punctuation]
  email = [word for word in email if len(word) > 1]
  email = [word for word in email if word.isalpha() == True]
  words += email

dictionary = Counter(words)

unique_num = len(dictionary)
total_num = sum(dictionary.values())

print("\nThe number of unique words in lingspam trainset: " + str(unique_num))
print("The total times they appeared: " + str(total_num))

print("The 20 most common words in trainset:")
print(*dictionary.most_common(20), sep='\n')

print('\nThe length of current dictionary: ' + str(len(dictionary)))


# calculate information gain

total_legit_emails = 0.0
total_spam_emails = 0.0

for index, row in lingspam_train_df.iterrows():
  is_spam = row['is_spam']
  if is_spam == 1:
    total_spam_emails += 1
  else:
    total_legit_emails += 1

print("total legit email number = {}".format(total_legit_emails))
print("total spam email number = {}".format(total_spam_emails))

p = total_legit_emails / (total_spam_emails + total_legit_emails)
print("p = {}".format(p))

h_c = -1 * p * math.log(p, 2) - (1 - p) * math.log(1 - p, 2)
print("H(C) = {}".format(h_c))


def count_legit_emails_with_word(word):
  num_legit_emails_with_word = 0
  for index, row in lingspam_train_df.iterrows():
    if row['is_spam'] == 0 and word in row['email_body'].split(' '):
      num_legit_emails_with_word += 1
  return num_legit_emails_with_word
      
def count_spam_emails_with_word(word):
  num_spam_emails_with_word = 0
  for index, row in lingspam_train_df.iterrows():
    if row['is_spam'] == 1 and word in row['email_body'].split(' '):
      num_spam_emails_with_word += 1
  return num_spam_emails_with_word

def h_legit_word_not_present(word):
  num_legit_emails_with_word = count_legit_emails_with_word(word)
  num_spam_emails_with_word = count_spam_emails_with_word(word)
  return (total_legit_emails - num_legit_emails_with_word) / (total_spam_emails + total_legit_emails) * math.log((total_legit_emails - num_legit_emails_with_word) / (total_spam_emails - num_spam_emails_with_word + total_legit_emails - num_legit_emails_with_word), 2)

def h_spam_word_not_present(word):
  num_legit_emails_with_word = count_legit_emails_with_word(word)
  num_spam_emails_with_word = count_spam_emails_with_word(word)
  return (total_spam_emails - num_spam_emails_with_word) / (total_spam_emails + total_legit_emails) * math.log((total_spam_emails - num_spam_emails_with_word) / (total_spam_emails - num_spam_emails_with_word + total_legit_emails - num_legit_emails_with_word), 2)

def h_legit_word_is_present(word):
  num_legit_emails_with_word = count_legit_emails_with_word(word)
  num_spam_emails_with_word = count_spam_emails_with_word(word)
  return num_legit_emails_with_word / (total_spam_emails + total_legit_emails) * math.log((num_legit_emails_with_word + 1) / (num_spam_emails_with_word + num_legit_emails_with_word + 2), 2)

def h_spam_word_is_present(word):
  num_legit_emails_with_word = count_legit_emails_with_word(word)
  num_spam_emails_with_word = count_spam_emails_with_word(word)
  return num_spam_emails_with_word / (total_spam_emails + total_legit_emails) * math.log((num_spam_emails_with_word + 1) / (num_spam_emails_with_word + num_legit_emails_with_word + 2), 2)

def info_gain(word):
  h_c_x = -1 * (h_legit_word_not_present(word) + h_spam_word_not_present(word) + h_legit_word_is_present(word) + h_spam_word_is_present(word))
  ig = h_c - h_c_x
  return ig


ig_l = []
for tup in dictionary.most_common(): 
    ig_d = {}
    word = tup[0]
    freq = tup[1]
    ig_d['word'] = word
    ig_d['freq'] = freq
    ig_d['ig'] = info_gain(word)
    ig_l.append(ig_d)
    print("word: {}, ig: {}".format(word, ig))


ig_path = '../data/ig.csv'
with codecs.open(ig_path, mode='w', encoding='utf8', errors='ignore') as out_file:
    writer = csv.DictWriter(out_file, ig_l[0].keys())
    writer.writeheader()
    for row in ig_l:
        writer.writerow(row)
