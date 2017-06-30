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
            if 'history_snapshot' in kwargs:
                snapshot = kwargs['history_snapshot']
                del kwargs['history_snapshot']
                print(snapshot)
                print(self.question_text)

            self.skip_history_when_saving = False

            try:
                ret = super(self.__class__, self).save(*args, **kwargs)
                # we use super().save to not update changed_recently to True
                # see VersionedModelMixin
            finally:
                self.skip_history_when_saving = True
            return ret
        setattr(cls, 'save_with_historical_record',
                save_with_historical_record)


def restore(instance, time):
    historical_instance = instance.history.as_of(time)
    # def restore(instance):
    for field in instance._meta.get_fields():
        if not field.auto_created:
            print(field.name)
            print(getattr(instance, field.name))
            print(getattr(historical_instance, field.name))
            setattr(instance, field.name, getattr(historical_instance, field.name))

    instance.save()
        # print(field.name)
        # print(field)
        # print(field.get_internal_type())
        # print(field.related_model)
        # print(field.model)
        # print(field.auto_created)
        # print(field.concrete)
        # print(field.many_to_many)
        # print('\n')
        # print(getattr(instance, field.name))


class Blahblah(models.Model):
    dsaasd = models.CharField(max_length=200)
    history = HistoricalRecords()

    def __str__(self):
        """Print func."""
        return self.dsaasd

class BaseModel(models.Model):
    history = ManualHistoricalRecords(inherit=True)
    testFIeld = models.CharField(max_length=200, default='', blank=True,
                                 null=True)

    class Meta:
        abstract = True


# https://stackoverflow.com/questions/2608067/how-to-find-out-whether-a-models-column-is-a-foreign-key

@python_2_unicode_compatible
class Question(BaseModel):
    """question."""

    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('date published')
    changed_recently = models.BooleanField(default=False)
    is_deleted = models.BooleanField(default=False)

    def __str__(self):
        """Print function."""
        return self.question_text

    def was_published_recently(self):
        """Ay."""
        return self.pub_date >= timezone.now() - datetime.timedelta(days=1)

    def save(self, *args, **kwargs):
        self.changed_recently = True
        super(Question, self).save(*args, **kwargs)

    def delete(self, *args, **kwargs):
        self.is_deleted = True
        self.changed_recently = True
        super(Question, self).save(*args, **kwargs)

    def completely_delete(self, *args, **kwargs):
        super(Question, self).delete(*args, **kwargs)

    def normal_save(self, *args, **kwargs):
        super(Question, self).save(*args, **kwargs)


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

# from polls.models import Question, ManualHistoricalRecords, Choice, restore
# from django.utils import timezone
# from simple_history.models import HistoricalRecords
# q = Question(question_text="Do you remember me", pub_date=timezone.now())
