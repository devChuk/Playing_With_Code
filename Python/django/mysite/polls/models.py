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
        super(ManualHistoricalRecords, self).contribute_to_class(cls, name)
        setattr(cls, 'skip_history_when_saving', True)

    def post_save(self, instance, created, **kwargs):
        if instance.skip_history_when_saving:
            return
        if not kwargs.get('raw', False):
            self.create_historical_record(instance, created and '+' or '~')

    def post_delete(self, instance, **kwargs):
        pass

    def add_extra_methods(self, cls):
        def save_with_historical_record(self, *args, **kwargs):
            """Save model with a historical record."""
            self.skip_history_when_saving = False
            try:
                ret = self.save(*args, **kwargs)
            finally:
                self.skip_history_when_saving = True
            return ret
        setattr(cls, 'save_with_historical_record',
                save_with_historical_record)


class BaseModel(models.Model):
    history = ManualHistoricalRecords(inherit=True)

    class Meta:
        abstract = True


@python_2_unicode_compatible
class Question(BaseModel):
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
class Choice(BaseModel):
    """choice."""

    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)

    def __str__(self):
        """Print func."""
        return self.choice_text
# Create your models here.

# from polls.models import Question, ManualHistoricalRecords, Choice
# from django.utils import timezone
# from simple_history.models import HistoricalRecords
# q = Question(question_text="Do you remember me", pub_date=timezone.now())
