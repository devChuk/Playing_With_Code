def restore(instance):
    for field in instance._meta.get_fields():
        print(field.name)
        print(field)
        print(field.get_internal_type())
        print(field.related_model)
        print(field.model)
        print(field.auto_created)
        print(field.concrete)
        print(field.many_to_many)
        print('\n')


>>> restore(q)
choice
<ManyToOneRel: polls.choice>
ForeignKey
<class 'polls.models.Choice'>
<class 'polls.models.Question'>
True
False
False


id
polls.Question.id
AutoField
None
<class 'polls.models.Question'>
True
True
None


question_text
polls.Question.question_text
CharField
None
<class 'polls.models.Question'>
False
True
None


pub_date
polls.Question.pub_date
DateTimeField
None
<class 'polls.models.Question'>
False
True
None


changed_recently
polls.Question.changed_recently
BooleanField
None
<class 'polls.models.Question'>
False
True
None


is_deleted
polls.Question.is_deleted
BooleanField
None
<class 'polls.models.Question'>
False
True
None


>>> restore(c)
id
polls.Choice.id
AutoField
None
<class 'polls.models.Choice'>
True
True
None


question
polls.Choice.question
ForeignKey
<class 'polls.models.Question'>
<class 'polls.models.Choice'>
False
True
False


choice_text
polls.Choice.choice_text
CharField
None
<class 'polls.models.Choice'>
False
True
None


votes
polls.Choice.votes
IntegerField
None
<class 'polls.models.Choice'>
False
True
None
