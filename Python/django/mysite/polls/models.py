# -*- coding: utf-8 -*-
"""question."""
from __future__ import unicode_literals

import datetime
from django.utils.encoding import python_2_unicode_compatible
from django.db import models
from django.utils import timezone


@python_2_unicode_compatible
class Question(models.Model):
    """question."""

    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('date published')

    def __str__(self):
        """Print function."""
        return self.question_text

    def was_published_recently(self):
        """Ay."""
        return self.pub_date >= timezone.now() - datetime.timedelta(days=1)


@python_2_unicode_compatible
class Choice(models.Model):
    """choice."""

    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)

    def __str__(self):
        """Print func."""
        return self.choice_text
# Create your models here.
