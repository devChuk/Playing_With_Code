# -*- coding: utf-8 -*-
"""question."""
from __future__ import unicode_literals

from django.db import models


class Question(models.Model):
    """question."""

    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('date published')


class Choice(models.Model):
    """choice."""

    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)
# Create your models here.
