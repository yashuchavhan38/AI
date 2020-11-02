# Email Spam Filter

## Introduction

In this project, we will design an e-mail spam ﬁlter using a Naïve Bayes and SVM based classiﬁcation on the ling-spam dataset.

## Dataset

The ling-spam corpus contains e-mails from the Linguist mailing list categorized as either legitimate or spam emails. The corpus is divided into four sub-folders that contain the same emails that are pre-processed with/without lemmatization and with/without stop-word removal. The e-mails in each sub-folder partitioned into 10 "folds".

In this project, we will use the ﬁrst 9 folds from the ling-spam corpus (lemm_stop folder, with both lemmatization and stop-word enabled) as training data, and the 10th fold as test data.

Download the whole ling-spam dataset from this [link](http://www.aueb.gr/users/ion/data/lingspam_public.tar.gz ).

Each one of the 10 subdirectories contains both spam and legitimate messages, one message in each file. Files whose names have the form spmsg*.txt are spam messages. All other files are legitimate messages.

## Feature Selection

Feature selection is performed using the information gain (IG) metric. From the training data, select the top-N features for N = {10, 100, 1000}. Note that feature selection based on the IG metric only accounts for the occurrence of (and not frequency with which terms appear) in the dataset.

## Classifiers

In the Jupyter notebook `email_spam_filter.ipynb`, 5 different classifiers are implemented.

Here is a list of email spam filters:

*  Naive Bayes Classifier
  * Bernoulli NB classiﬁer with binary features
  * Multinomial NB with binary features
  * Multinomial NB with term frequency (TF) features
* SVM based Classifier
* Adversarial Classification

For the last but not least classifier, which is "Adversarial Classifier", is an approach to update NB based e-mail spam ﬁlters in response to attacks that try to evade a basic NB ﬁlter. It is inspired from [paper](https://dl.acm.org/doi/10.1145/1014052.1014066).