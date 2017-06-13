# -*- coding: utf-8 -*-
"""question."""
from __future__ import unicode_literals

import datetime
from django.utils.encoding import python_2_unicode_compatible
from django.db import models
from django.utils import timezone
from simple_history.models import HistoricalRecords


class ManualHistoricalRecords(HistoricalRecords):
    def contribute_to_class(self, cls, name):
        self.manager_name = name
        self.module = cls.__module__
        self.cls = cls
        setattr(cls, 'skip_history_when_saving', True)
        models.signals.class_prepared.connect(self.finalize, weak=False)
        self.add_extra_methods(cls)

    def add_extra_methods(self, cls):
        def save_with_historical_record(self, *args, **kwargs):
            """Save model with a historical record."""
            delattr(self.__class__, 'skip_history_when_saving')
            try:
                ret = self.save(*args, **kwargs)
            finally:
                setattr(self.__class__, 'skip_history_when_saving', True)
            return ret
        setattr(cls, 'save_with_historical_record',
                save_with_historical_record)


@python_2_unicode_compatible
class Question(models.Model):
    """question."""

    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('date published')
    history = ManualHistoricalRecords()

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
    history = ManualHistoricalRecords()

    def __str__(self):
        """Print func."""
        return self.choice_text
# Create your models here.

# from polls.models import Question, ManualHistoricalRecords, Choice
# from django.utils import timezone
# from simple_history.models import HistoricalRecords
# q = Question(question_text="Do you remember me", pub_date=timezone.now())