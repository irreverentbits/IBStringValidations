// Copyright 2013 Lee Calloway
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#import "UITextField+IBTextValidation.h"

#import <objc/runtime.h>

#import "IBStringValidator.h"


static char const * const kObjectKey = "IBStringValidator";


@implementation UITextField (IBTextValidation)

- (IBStringValidator*)ibStringValidator;
{
	return objc_getAssociatedObject(self, kObjectKey);
}

- (void)ibSetStringValidator:(IBStringValidator*)stringValidator;
{
	// Remove any existing string validator before assigning a new one
	[self ibRemoveStringValidator];
		
	// If nil was passed for the stringValidator, there is no need to continue
	if (!stringValidator)
	{
		return;
	}
	
	// Set provided string validator as new associated object
	objc_setAssociatedObject(self, kObjectKey, stringValidator, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
	
    // Capture changes to this text field's text that come from user input
    [self addTarget:self action:@selector(ibUpdateValidity) forControlEvents:UIControlEventEditingChanged];

    // Capture changes to this label's text that come from programatic setting of the text property
	[self addObserver:stringValidator forKeyPath:@"text" options:0 context:NULL];
	
	[self ibUpdateValidity];
}

- (void)ibRemoveStringValidator;
{
	IBStringValidator* currentValidator = [self ibStringValidator];
	if (currentValidator)
	{
		[self removeTarget:self action:@selector(ibUpdateValidity) forControlEvents:UIControlEventEditingChanged];
		[self removeObserver:currentValidator forKeyPath:@"text"];
	}
	
	objc_setAssociatedObject(self, kObjectKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ibUpdateValidity;
{	
	[[self ibStringValidator] updateValidityForString:self.text];
}

@end